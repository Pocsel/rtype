
#ifndef ITCPSOCKETPROXY_HPP_
# define ITCPSOCKETPROXY_HPP_

#include "ITcpSocket.hpp"
#include "Packet.hpp"
#include "functor.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ITcpSocketProxy
        {
        private:
            typedef FUNCTOR1(bool) WriteHandler;
        public:
            virtual ~ITcpSocketProxy(void) {}

            virtual void pc_PushRawData(char const* data, size_t size) = 0;
            virtual Packet* pc_GetPacket(void) = 0;

            virtual void Send(Packet const& packet) = 0;
            virtual bool HasSomethingToSend(void) const = 0;
            virtual ssize_t SendOnNetwork(void) = 0;
            virtual ITcpSocket& GetSocket(void) = 0;

            virtual void ActivateWriteHandling(WriteHandler const& handler) = 0;
            virtual void DeactivateWriteHandling(void) = 0;
        };

    }
}

#endif // !ITCPSOCKETPROXY_HPP_
