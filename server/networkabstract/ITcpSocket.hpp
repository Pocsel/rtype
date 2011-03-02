
#ifndef ITCPSOCKET_HPP_
# define ITCPSOCKET_HPP_

#include "SocketFD.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ITcpSocket
        {
        public:
            virtual ~ITcpSocket(void) {}

            virtual ssize_t Send(char const* data, size_t len) = 0;
            virtual ssize_t Recv(char* buf, size_t len) = 0;
            virtual ITcpSocket* Accept(void) = 0;
            virtual SocketFD GetSocketFD(void) const = 0;
        };

    }
}

#endif // !ITCPSOCKET_HPP_
