
#ifndef CLIENT_HPP_
# define CLIENT_HPP_

#include <fstream>

#include "ITcpSocket.hpp"
#include "IService.hpp"
#include "String.hpp"
#include "TcpSocketProxy.hpp"
#include "IGame.hpp"
#include "PacketCreator.hpp"
#include "Mutex.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Server;

        class Client
        {
        private:
            enum State
            {
                JUST_ARRIVED,
                AUTHENTIFIED,
                IN_GAME
            };

        public:
            Client(ITcpSocket* socket, IService* service, Server& server, uint16_t id);
            ~Client(void);

            uint16_t GetId(void) const;
            String const& GetNick(void) const;
            ITcpSocket& GetSocket(void);
            void SendTcpPacket(Packet const& packet);

            bool DidPong(void) const;
            void Ping(void);

        private:
            bool _ReadHandler(int errorCode, char* data, size_t len);
            bool _ParsePacket(Packet& packet);

            bool _AnyoneThereHandler(Packet& packet);
            bool _INeedThisHandler(Packet& packet);
            bool _LetsGoHandler(Packet& packet);
            bool _PingHandler(Packet& packet);
            bool _PongHandler(Packet& packet);

            bool _WriteFile(void);

            std::map<uint8_t, bool (Client::*)(Packet&)> _handlers;

            uint16_t _id;
            String _nick;

            PacketCreator _packetCreator;
            ITcpSocket* _socket;
            ITcpSocketProxy* _socketProxy;
            Server& _server;

            State _state;
            bool _didPong;

            std::queue<uint16_t> _fileQueue;
            std::ifstream* _file;
            bool _sendingFile;

            bool _isDone;
        };

    }
}

#endif /* !CLIENT_HPP_ */
