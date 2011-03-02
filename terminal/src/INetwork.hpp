#ifndef __INETWORK_HPP__
#define __INETWORK_HPP__

#include "String.hpp"
#include "Packet.hpp"

namespace Gmgp
{
    namespace Terminal
    {

        class INetwork
        {
            public:
                virtual ~INetwork() {}
                virtual void Connect(String const& ip, unsigned short port) = 0;
                virtual String const& GetHost() const = 0;
                virtual void SendTcpPacket(Packet const& packet) = 0;
                virtual uint16_t GetClientId() const = 0;
                virtual void SetClientId(uint16_t clientId) = 0;
        };

    }
}

#endif

