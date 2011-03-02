
#include "PacketCreator.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        PacketCreator::PacketCreator(void)
        {
        }

        PacketCreator::~PacketCreator(void)
        {
        }

        void PacketCreator::CreatePing(Packet& packet)
        {
            packet.Write8(Packet::PING);
            packet.WriteString("Y A L A P _ A");
        }

        void PacketCreator::CreatePong(Packet& packet, Packet& ping)
        {
            packet.Write8(Packet::PONG);
            packet.WriteString(ping.ReadString());
        }

        void PacketCreator::CreatePleaseComeIn(Packet& packet, uint16_t id, uint16_t itemsCount)
        {
            packet.Write8(Packet::PLEASE_COME_IN);
            packet.Write16(id);
            packet.Write16(itemsCount);
        }

        void PacketCreator::CreateTakeThis(Packet& packet, uint16_t fileId, size_t size)
        {
            packet.Write8(Packet::TAKE_IT);
            packet.Write16(fileId);
            packet.Write32(size);
        }

    }
}
