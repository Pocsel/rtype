
#ifndef WINDOWSTCPSOCKET_HPP_
# define WINDOWSTCPSOCKET_HPP_

#include "ITcpSocket.hpp"
#include "SocketFD.hpp"
#include "HostAddress.hpp"

namespace Gmgp
{
    namespace Server
    {

        class WindowsTcpSocket : public ITcpSocket
        {
        public:
            /// Constructor for creating an "Acceptor" socket
            WindowsTcpSocket(HostAddress const& address);

            /// Constructor for creating a read/write socket after a successful accept
            WindowsTcpSocket(SocketFD socket);

            ~WindowsTcpSocket(void);

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

#endif // !WINDOWSTCPSOCKET_HPP_
