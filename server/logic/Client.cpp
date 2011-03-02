
#include "Client.hpp"
#include "Server.hpp"
#include "Packet.hpp"
#include "functor.hpp"
#include "Log.hpp"
#include "ScopeLock.hpp"

namespace Gmgp
{
    namespace Server
    {

        Client::Client(ITcpSocket* socket, IService* service, Server& server, uint16_t id)
            : _id(id), _socket(socket), _server(server),
            _state(JUST_ARRIVED),
            _didPong(true),
            _file(0),
            _sendingFile(false),
            _isDone(false)
        {
            this->_handlers[Packet::ANYONE_THERE] = &Client::_AnyoneThereHandler;
            this->_handlers[Packet::I_NEED_THIS] = &Client::_INeedThisHandler;
            this->_handlers[Packet::LETS_GO] = &Client::_LetsGoHandler;
            this->_handlers[Packet::PING] = &Client::_PingHandler;
            this->_handlers[Packet::PONG] = &Client::_PongHandler;

            this->_socketProxy =
                &service->RegisterTcpSocket(*this->_socket,
                                            b00st::bind(&Client::_ReadHandler, *this));
        }

        Client::~Client(void)
        {
            delete this->_file;
        }

        uint16_t Client::GetId(void) const
        {
            return this->_id;
        }

        String const& Client::GetNick(void) const
        {
            return this->_nick;
        }

        ITcpSocket& Client::GetSocket(void)
        {
            return *this->_socket;
        }

        void Client::SendTcpPacket(Packet const& packet)
        {
            this->_socketProxy->Send(packet);
        }

        bool Client::DidPong(void) const
        {
            return this->_didPong;
        }

        void Client::Ping(void)
        {
            if (this->_sendingFile == false)
                this->_didPong = false;
            Packet ping;
            this->_packetCreator.CreatePing(ping);
            this->SendTcpPacket(ping);
        }

        bool Client::_ReadHandler(int errorCode, char* data, size_t len)
        {
            if (errorCode == -1)
            {
                this->_server.RemoveClient(this->_id);
                delete this->_socketProxy;
                delete this;
                return true;
            }
            this->_socketProxy->pc_PushRawData(data, len);
            Packet* packet;
            while ((packet = this->_socketProxy->pc_GetPacket()) != 0)
            {
                if (this->_ParsePacket(*packet))
                {
                    delete packet;
                    this->_server.RemoveClient(this->_id);
                    delete this->_socketProxy;
                    delete this;
                    return true;
                }
                delete packet;
                if (this->_isDone == true)
                {
                    this->_server.RemoveClient(this->_id);
                    delete this;
                    return true;
                }
            }
            return false;
        }

        bool Client::_ParsePacket(Packet& packet)
        {
            try
            {
                uint8_t type = packet.Read8();
                if (this->_handlers.find(type) == this->_handlers.end())
                {
                    Log::I("Unknown packet type : Client out !");
                    packet.Dump();
                    return true;
                }
                return (this->*this->_handlers[type])(packet);
            }
            catch (std::exception&)
            {
                Log::I("Someone sent a wrong packet : out !");
                packet.Dump();
                return true;
            }
            return false;
        }

        bool Client::_AnyoneThereHandler(Packet& packet)
        {
            if (packet.ReadString() != "hallal_a = close")
            {
                Log::I("Wrong Magic string: Client out.");
                return true;
            }
            this->_nick = packet.ReadString();
            if (this->_nick.size() > 10)
            {
                Log::I("Too long nick: Client out.");
                return true;
            }

            bool isValid = false;
            for (String::iterator it = this->_nick.begin(),
                 ite = this->_nick.end() ; it != ite ; ++it)
            {
                if (*it > ' ' && *it <= '~')
                {
                    isValid = true;
                    break;
                }
            }
            if (isValid == false)
            {
                Log::I("Invalid nick: Client out.");
                return true;
            }

            this->_state = AUTHENTIFIED;

            std::map<uint16_t, AResourceInfo*> const& resources = this->_server.GetResources();

            {
                Packet pleaseComeIn;
                this->_packetCreator.CreatePleaseComeIn(pleaseComeIn, this->_id, resources.size());
                this->SendTcpPacket(pleaseComeIn);
            }

            for (std::map<uint16_t, AResourceInfo*>::const_iterator it = resources.begin(),
                 ite = resources.end() ; it != ite ; ++it)
            {
                Packet iHaveThis;
                it->second->FillPacket(iHaveThis);
                this->SendTcpPacket(iHaveThis);
            }

            return false;
        }

        bool Client::_INeedThisHandler(Packet& packet)
        {
            if (this->_sendingFile)
            {
                this->_fileQueue.push(packet.Read16());
                return false;
            }
            this->_sendingFile = true;

            uint16_t fileId = packet.Read16();
            size_t size;
            this->_file = this->_server.GetFile(fileId, size);
            if (this->_file == 0)
            {
                this->_sendingFile = false;
                return false;
            }
            Packet takeThis;
            this->_packetCreator.CreateTakeThis(takeThis, fileId, size);
            this->SendTcpPacket(takeThis);

            char buff[4096];
            buff[0] = Packet::TAKE_SOME_MORE;
            this->_file->read(buff + 1, 4095);
            Packet dataPacket;
            dataPacket.WriteData(buff, this->_file->gcount() + 1);
            this->SendTcpPacket(dataPacket);

            this->_socketProxy->ActivateWriteHandling(b00st::bind(&Client::_WriteFile, *this));

            return false;
        }

        bool Client::_LetsGoHandler(Packet& packet)
        {
            packet.Read16(); // unused Port

            this->_server.PutClientIngame(this, this->_socketProxy);
            this->_isDone = true;
            return false;
        }

        bool Client::_PingHandler(Packet& packet)
        {
            Packet pong;
            this->_packetCreator.CreatePong(pong, packet);
            this->SendTcpPacket(pong);
            return false;
        }

        bool Client::_PongHandler(Packet&)
        {
            this->_didPong = true;
            return false;
        }

        bool Client::_WriteFile(void)
        {
            if (this->_file->eof())
            {
                delete this->_file;
                this->_file = 0;
                if (this->_fileQueue.empty())
                {
                    this->_sendingFile = false;
                    return true;
                }

                uint16_t fileId = this->_fileQueue.front();
                this->_fileQueue.pop();
                size_t size;
                this->_file = this->_server.GetFile(fileId, size);
                if (this->_file == 0)
                {
                    this->_sendingFile = false;
                    return true;
                }
                Packet takeThis;
                this->_packetCreator.CreateTakeThis(takeThis, fileId, size);
                this->SendTcpPacket(takeThis);
            }

            char buff[4096];
            buff[0] = Packet::TAKE_SOME_MORE;
            this->_file->read(buff + 1, 4095);
            Packet dataPacket;
            dataPacket.WriteData(buff, this->_file->gcount() + 1);
            this->SendTcpPacket(dataPacket);
            return false;
        }

    }
}
