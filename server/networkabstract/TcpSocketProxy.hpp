
#ifndef TCPSOCKETPROXY_HPP_
# define TCPSOCKETPROXY_HPP_

#include <queue>
#include <map>
#include <list>

#include "ITcpSocketProxy.hpp"
#include "ITcpSocket.hpp"
#include "Packet.hpp"
#include "SendBuffer.hpp"
#include "functor.hpp"

namespace Gmgp
{
    namespace Server
    {

        class TcpSocketProxy : public ITcpSocketProxy
        {
        private:
            typedef FUNCTOR1(bool) WriteHandler;

        public:
            TcpSocketProxy(ITcpSocket& socket);
            virtual ~TcpSocketProxy(void);

            virtual void pc_PushRawData(char const* data, size_t size);
            virtual Packet* pc_GetPacket(void);

            virtual void Send(Packet const& packet);
            virtual bool HasSomethingToSend(void) const;
            virtual ssize_t SendOnNetwork(void);
            virtual ITcpSocket& GetSocket(void);

            virtual void ActivateWriteHandling(WriteHandler const& handler);
            virtual void DeactivateWriteHandling(void);

        private:
            char* _pc_rawData;
            size_t _pc_rawDataSize;

            ITcpSocket& _socket;
            std::list<SendBuffer> _buff;
            WriteHandler _writeHandler;
            bool _writeHandling;
        };

    }
}

#endif // !TCPSOCKETPROXY_HPP_
