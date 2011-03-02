
#include <stdexcept>
#include <iostream>

#include "WindowsTcpSocket.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        WindowsTcpSocket::WindowsTcpSocket(HostAddress const& address) : _acceptor(true)
        {
            WSADATA wsaData;
            int err = ::WSAStartup(MAKEWORD(2,2), &wsaData);
            if (err)
                throw std::runtime_error(String("tcp: WSAStartup() failure: ") + err);

            struct ::protoent *pe;
            struct ::sockaddr_in sin;

            if ((pe = ::getprotobyname("tcp")) == 0)
                throw std::runtime_error(String("tcp: getprotobyname() failure: ") + ::WSAGetLastError());
            if ((this->_socket = socket(PF_INET, SOCK_STREAM, pe->p_proto)) == -1)
                throw std::runtime_error("tcp: socket() failure");
            sin.sin_family = AF_INET;
            sin.sin_port = htons(address.GetPort());
            sin.sin_addr.s_addr = htonl(INADDR_ANY);
            int yes = 1;
            if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&yes), sizeof(int)) == -1)
                throw std::runtime_error("tcp: setsockopt() failure");
            if (bind(this->_socket, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin)) == -1)
                throw std::runtime_error("tcp: bind() failure");
            if (listen(this->_socket, 23) == -1)
                throw std::runtime_error("tcp: listen() failure");
        }

        WindowsTcpSocket::WindowsTcpSocket(SocketFD socket) : _socket(socket), _acceptor(false)
        {
        }

        WindowsTcpSocket::~WindowsTcpSocket(void)
        {
            if (::closesocket(this->_socket) == -1)
                Log::W("Could not close a TCP socket properly.");
        }

        ssize_t WindowsTcpSocket::Send(char const* data, size_t len)
        {
            if (this->_acceptor == false)
                return ::send(this->_socket, data, len, 0);
            throw std::runtime_error("cannot send with an acceptor");
        }

        ssize_t WindowsTcpSocket::Recv(char* buf, size_t len)
        {
            if (this->_acceptor == false)
                return ::recv(this->_socket, buf, len, 0);
            throw std::runtime_error("cannot recv with an acceptor");
        }

        ITcpSocket* WindowsTcpSocket::Accept(void)
        {
            if (this->_acceptor == true)
            {
                struct ::sockaddr_in csin;
                int len = sizeof(csin);

                SocketFD socket;
                if ((socket = accept(this->_socket, reinterpret_cast<struct ::sockaddr *>(&csin), &len)
                    ) == -1)
                    throw std::runtime_error("Accept() flailure");

                return new WindowsTcpSocket(socket);
            }
            else
                throw std::runtime_error("cannot accept with an non acceptor socket");
        }

        SocketFD WindowsTcpSocket::GetSocketFD(void) const
        {
            return this->_socket;
        }

    }
}
