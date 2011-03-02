
#include <stdexcept>

#include "TcpSocketProxy.hpp"

namespace Gmgp
{
    namespace Server
    {

        TcpSocketProxy::TcpSocketProxy(ITcpSocket& socket)
            : _pc_rawData(0), _pc_rawDataSize(0),
            _socket(socket), _writeHandling(false)
        {
        }

        TcpSocketProxy::~TcpSocketProxy(void)
        {
            if (this->_pc_rawData)
                delete[] this->_pc_rawData;
            delete &this->_socket;
        }

        void TcpSocketProxy::pc_PushRawData(char const* data, size_t size)
        {
            char* newData = new char[this->_pc_rawDataSize + size];
            for (size_t i = 0 ; i < this->_pc_rawDataSize + size ; ++i)
                newData[i] = (i < this->_pc_rawDataSize ? this->_pc_rawData[i] : data[i]);
            delete[] this->_pc_rawData;
            this->_pc_rawData = newData;
            this->_pc_rawDataSize += size;
        }

        Packet* TcpSocketProxy::pc_GetPacket(void)
        {
            if (this->_pc_rawDataSize > 2)
            {
                uint16_t packetSize = ((this->_pc_rawData[0] << 8) & 0xFF00) | this->_pc_rawData[1];

                if (this->_pc_rawDataSize >= packetSize + 2u)
                {
                    Packet* nuPacket = new Packet();
                    nuPacket->WriteData(this->_pc_rawData + 2, packetSize);
                    this->_pc_rawDataSize -= packetSize + 2;
                    for (size_t i = 0 ; i < this->_pc_rawDataSize ; ++i)
                        this->_pc_rawData[i] = this->_pc_rawData[packetSize + 2 + i];
                    return nuPacket;
                }
            }
            return 0;
        }

        void TcpSocketProxy::Send(Packet const& packet)
        {
            this->_buff.push_back(SendBuffer(packet.GetCompleteData(), packet.GetCompleteSize(), false));
        }

        bool TcpSocketProxy::HasSomethingToSend(void) const
        {
            return this->_buff.empty() == false;
        }

        ssize_t TcpSocketProxy::SendOnNetwork(void)
        {
            if (this->_buff.empty())
                throw std::runtime_error("TcpSocketProxy: Cannot Send Nothing On Network");

            ssize_t len;

            len = this->_socket.Send(this->_buff.front().GetData(), this->_buff.front().GetLenght());

            if (len > 0)
                if (this->_buff.front().Remove(len))
                    this->_buff.pop_front();

            if (this->_writeHandling && this->_buff.empty())
                if (this->_writeHandler())
                    this->_writeHandling = false;

            return len;
        }

        ITcpSocket& TcpSocketProxy::GetSocket(void)
        {
            return this->_socket;
        }

        void TcpSocketProxy::ActivateWriteHandling(WriteHandler const& handler)
        {
            this->_writeHandling = true;
            this->_writeHandler = handler;
        }

        void TcpSocketProxy::DeactivateWriteHandling(void)
        {
            this->_writeHandling = false;
        }

    }
}
