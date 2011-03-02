
#ifndef HOSTADDRESS_HPP_
# define HOSTADDRESS_HPP_

#include "ITcpSocket.hpp"

namespace Gmgp
{
    namespace Server
    {

        class HostAddress
        {
        private:
#ifdef _WIN32 //windows
            enum errorCode
            {
                GSN_ERROR = SOCKET_ERROR,
            };
#else //unix
            enum errorCode
            {
                GSN_ERROR = -1,
            };
#endif

        public:
            HostAddress();
            HostAddress(uint16_t port, uint32_t ip = 0);
            HostAddress(ITcpSocket const& tcpSocket, uint16_t port = 0);

            void SetIp(uint32_t ip);
            void SetPort(uint16_t port);

            uint32_t GetIp(void) const;
            uint16_t GetPort(void) const;

            void Dump(void) const;

            bool operator ==(HostAddress const& other) const;
            bool operator <(HostAddress const& other) const;
            bool operator >(HostAddress const& other) const;

        private:
            uint32_t _ip;
            uint16_t _port;
        };

    }
}

#endif // !HOSTADDRESS_HPP_
