
#ifndef PACKETCREATOR_HPP_
# define PACKETCREATOR_HPP_

#include "Packet.hpp"

namespace Gmgp
{
    namespace Server
    {

        class PacketCreator
        {
        public:
            PacketCreator(void);
            ~PacketCreator(void);

            void CreatePing(Packet& packet);
            void CreatePong(Packet& packet, Packet& ping);
            void CreatePleaseComeIn(Packet& packet, uint16_t id, uint16_t itemsCount);
            void CreateTakeThis(Packet& packet, uint16_t fileId, size_t size);

        private:
            char* _rawData;
            size_t _rawDataSize;
        };

    }
}

#endif // !PACKETCREATOR_HPP_
