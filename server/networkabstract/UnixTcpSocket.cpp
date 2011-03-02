
#include <stdexcept>
#include <iostream>

#include <sys/socket.h>
#include <netdb.h>

#include "UnixTcpSocket.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        UnixTcpSocket::UnixTcpSocket(HostAddress const& address) : _acceptor(true)
        {
            struct ::protoent *pe;
            struct ::sockaddr_in sin;

            if ((pe = getprotobyname("tcp")) == 0)
                throw std::runtime_error("tcp: getprotobyname() failure");
            if ((this->_socket = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
                throw std::runtime_error("tcp: socket() failure");
            sin.sin_family = AF_INET;
            sin.sin_port = htons(address.GetPort());
            sin.sin_addr.s_addr = htonl(INADDR_ANY);
            int yes = 1;
            if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
                throw std::runtime_error("tcp: setsockopt() failure");
            if (bind(this->_socket, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin)) == -1)
                throw std::runtime_error("tcp: bind() failure");
            if (listen(this->_socket, 23) == -1)
                throw std::runtime_error("tcp: listen() failure");
        }

        UnixTcpSocket::UnixTcpSocket(SocketFD socket) : _socket(socket), _acceptor(false)
        {
        }

        UnixTcpSocket::~UnixTcpSocket(void)
        {
            if (close(this->_socket) == -1)
                Log::W("Could not close a TCP socket properly.");
        }

        ssize_t UnixTcpSocket::Send(char const* data, size_t len)
        {
            if (this->_acceptor == false)
                return ::write(this->_socket, data, len);
            throw std::runtime_error("cannot send with an acceptor");
        }

        ssize_t UnixTcpSocket::Recv(char* buf, size_t len)
        {
            if (this->_acceptor == false)
                return ::read(this->_socket, buf, len);
            throw std::runtime_error("cannot recv with an acceptor");
        }

        ITcpSocket* UnixTcpSocket::Accept(void)
        {
            if (this->_acceptor == true)
            {
                unsigned int len;
                struct ::sockaddr_in csin;
                len = sizeof(csin);

                SocketFD socket;
                if ((socket = accept(this->_socket, reinterpret_cast<struct ::sockaddr *>(&csin), &len)
                    ) == -1)
                    throw std::runtime_error("Accept() flailure");

                return new UnixTcpSocket(socket);
            }
            else
                throw std::runtime_error("cannot accept with an non acceptor socket");
        }

        SocketFD UnixTcpSocket::GetSocketFD(void) const
        {
            return this->_socket;
        }

    }
}
