
#ifndef UNIXTCPSOCKET_HPP_
# define UNIXTCPSOCKET_HPP_

#include "ITcpSocket.hpp"
#include "SocketFD.hpp"
#include "HostAddress.hpp"

namespace Gmgp
{
    namespace Server
    {

        class UnixTcpSocket : public ITcpSocket
        {
        public:
            /// Constructor for creating an "Acceptor" socket
            UnixTcpSocket(HostAddress const& address);

            /// Constructor for creating a read/write socket after a successful accept
            UnixTcpSocket(SocketFD socket);

            ~UnixTcpSocket(void);

            virtual ssize_t Send(char const* data, size_t len);
            virtual ssize_t Recv(char* buf, size_t len);
            virtual ITcpSocket* Accept(void);
            virtual SocketFD GetSocketFD(void) const;

        private:
            SocketFD _socket;
            bool _acceptor;
        };

    }
}

#endif // !UNIXTCPSOCKET_HPP_
