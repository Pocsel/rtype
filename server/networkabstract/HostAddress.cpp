
#include <iostream>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include "HostAddress.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        HostAddress::HostAddress() :
            _ip(0), _port(0)
        {
        }

        HostAddress::HostAddress(uint16_t port, uint32_t ip) : _ip(ip), _port(port)
        {
        }

        HostAddress::HostAddress(ITcpSocket const& tcpSocket, uint16_t port) : _port(port)
        {
            struct ::sockaddr_in sa;
            int size = sizeof(sa);
            if (getpeername(tcpSocket.GetSocketFD(), reinterpret_cast<struct ::sockaddr*>(&sa),
                            reinterpret_cast<socklen_t*>(&size)) == GSN_ERROR)
                throw std::runtime_error("getsockname() failure");
            if (size != sizeof(sa))
                throw std::runtime_error("getsockname() failure 2");
            this->_ip = ntohl(sa.sin_addr.s_addr);
        }

        void HostAddress::SetIp(uint32_t ip)
        {
            this->_ip = ip;
        }

        void HostAddress::SetPort(uint16_t port)
        {
            this->_port = port;
        }

        uint32_t HostAddress::GetIp(void) const
        {
            return this->_ip;
        }

        uint16_t HostAddress::GetPort(void) const
        {
            return this->_port;
        }

        void HostAddress::Dump(void) const
        {
            std::cout << "Dump HostAddress:" << std::endl;

            std::cout << "ip: " <<
                ((this->_ip & 0xFF000000) >> 24) << "." <<
                ((this->_ip & 0x00FF0000) >> 16) << "." <<
                ((this->_ip & 0x0000FF00) >> 8) << "." <<
                ((this->_ip & 0x000000FF)) << std::endl;

            std::cout << "port: " << this->_port << std::endl;
        }

        bool HostAddress::operator ==(HostAddress const& other) const
        {
            return this->_port == other._port && this->_ip == other._ip;
        }

        bool HostAddress::operator <(HostAddress const& other) const
        {
            return this->_ip == other._ip ? this->_port < other._port : this->_ip < other._ip;
        }

        bool HostAddress::operator >(HostAddress const& other) const
        {
            return this->_ip == other._ip ? this->_port > other._port : this->_ip > other._ip;
        }

    }
}
