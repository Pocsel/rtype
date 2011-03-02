#ifndef __ITEMMANAGER_HPP__
#define __ITEMMANAGER_HPP__

#include <map>

#include "NonCopyable.hpp"
#include "Item.hpp"
#include "Constants.hpp"
#include "Packet.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename Entity, typename Player>
        class ItemManager :
            private b00st::NonCopyable
        {
            public:
                ItemManager(BasicGame<Entity, Player>& game) :
                    _game(game), _itemId(1), _packet(0)
                {
                }

                ~ItemManager()
                {
                    std::map<size_t, Packet*>::iterator it = this->_buffers.begin();
                    std::map<size_t, Packet*>::iterator itEnd = this->_buffers.end();
                    for (; it != itEnd; ++it)
                        delete it->second;
                    delete this->_packet;
                }

                void ConfirmItems(uint32_t, Packet const&, Player const&)
                {
                }

                uint32_t SendItem(Item& item)
                {
                    this->_AddItemToBuffers(&item, this->_itemId, false);
                    ++this->_itemId;
                    return this->_itemId - 1;
                }

                void Run(float time)
                {
                    std::map<Item*, uint32_t>::iterator it = this->_items.begin();
                    std::map<Item*, uint32_t>::iterator itEnd = this->_items.end();
                    for (; it != itEnd; ++it)
                    {
                        it->first->Run(time);
                        if (it->first->HasChanged())
                            this->_AddItemToBuffers(it->first, it->second, false);
                        it->first->ResetParamMask();
                        it->first->SetChanged(false);
                    }
                    this->_SendPackets();
                }

                void RefreshPlayer(uint16_t playerId)
                {
                    std::map<Item*, uint32_t>::iterator it = this->_items.begin();
                    std::map<Item*, uint32_t>::iterator itEnd = this->_items.end();
                    for (; it != itEnd; ++it)
                        if (it->first->GetPlayerId() == 0 || it->first->GetPlayerId() == playerId)
                        {
                            Packet* p = this->_GetPacketOfPlayer(playerId);
                            if (p == 0)
                                continue;
                            p->Write8(1);
                            p->Write32(it->second);
                            uint16_t mask = 0;
                            mask |= RESOURCE_ID;
                            mask |= X_POS;
                            mask |= Y_POS;
                            mask |= X_SPEED;
                            mask |= Y_SPEED;
                            mask |= X_ACCEL;
                            mask |= Y_ACCEL;
                            mask |= LIFE_TIME_MS;
                            mask |= LIFE_TIME_CYCLES;
                            mask |= Z_POS;
                            mask |= BLINKING;
                            mask |= FRAME;
                            mask |= LUA_ID;
                            if (it->first->GetDisapear())
                                mask |= DISAPEAR;
                            if (it->first->GetCursor())
                                mask |= CURSOR;
                            p->Write16(mask);
                            p->Write16(it->first->GetResourceId());
                            p->WriteFloat(it->first->GetPositionX());
                            p->WriteFloat(it->first->GetPositionY());
                            p->WriteFloat(it->first->GetSpeedX());
                            p->WriteFloat(it->first->GetSpeedY());
                            p->WriteFloat(it->first->GetAccelX());
                            p->WriteFloat(it->first->GetAccelY());
                            p->Write16(it->first->GetLifeTimeMs());
                            p->Write8(it->first->GetLifeTimeCycles());
                            p->Write8(it->first->GetPositionZ());
                            p->Write16(it->first->GetBlinking());
                            p->Write16(it->first->GetFrame());
                            p->Write16(it->first->GetLuaId());
                        }
                }

                void RemoveAllItemsOfPlayer(uint16_t playerId)
                {
                    Log::D("Removing all items of player " + String(playerId) + ".");
                    Packet* p = this->_GetPacketOfPlayer(playerId);
                    if (p == 0)
                        return;
                    p->Write8(0);
                }

                void SendDeletionForItemsOfPlayer(uint16_t playerId)
                {
                    std::map<Item*, uint32_t>::iterator it = this->_items.begin();
                    std::map<Item*, uint32_t>::iterator itEnd = this->_items.end();
                    for (; it != itEnd; ++it)
                        if (it->first->GetPlayerId() == 0 || it->first->GetPlayerId() == playerId)
                        {
                            Packet* p = this->_GetPacketOfPlayer(playerId);
                            if (p == 0)
                                continue;
                            p->Write8(1);
                            p->Write32(it->second);
                            p->Write16(0); // mask 0 = deletion
                        }
                }

                bool AddItem(Item* item)
                {
                    if (this->_items.count(item) != 0)
                        return false;
                    this->_items[item] = _itemId;
                    ++this->_itemId;
                    return true;
                }

                bool RemoveItem(Item* item, bool sendPacket = true, bool updateItem = false)
                {
                    if (this->_items.count(item) == 0)
                        return false;
                    if (sendPacket)
                        this->_AddItemToBuffers(item, this->_items[item], true);
                    else if (updateItem && item->HasChanged())
                        this->_AddItemToBuffers(item, this->_items[item], false);
                    this->_items.erase(item);
                    return true;
                }

                size_t GetNumberOfItems() const
                {
                    return this->_items.size();
                }

                bool HasItem(Item* item) const
                {
                    return this->_items.count(item) == 1;
                }

            private:
                enum
                {
                    MAXPACKETSIZE = 512
                };

                void _AddItemToBuffers(Item* item, uint32_t id, bool deletion)
                {
                    Packet* p = this->_GetPacketOfPlayer(item->GetPlayerId());
                    if (p == 0)
                        return;
                    p->Write8(1);
                    p->Write32(id);
                    if (deletion)
                    {
                        p->Write16(0); // mask 0 = deletion
                        return;
                    }
                    uint16_t mask = item->GetParamMask();
                    p->Write16(mask);
                    if (mask & RESOURCE_ID)
                        p->Write16(item->GetResourceId());
                    if (mask & X_POS)
                        p->WriteFloat(item->GetPositionX());
                    if (mask & Y_POS)
                        p->WriteFloat(item->GetPositionY());
                    if (mask & X_SPEED)
                        p->WriteFloat(item->GetSpeedX());
                    if (mask & Y_SPEED)
                        p->WriteFloat(item->GetSpeedY());
                    if (mask & X_ACCEL)
                        p->WriteFloat(item->GetAccelX());
                    if (mask & Y_ACCEL)
                        p->WriteFloat(item->GetAccelY());
                    if (mask & LIFE_TIME_MS)
                        p->Write16(item->GetLifeTimeMs());
                    if (mask & LIFE_TIME_CYCLES)
                        p->Write8(item->GetLifeTimeCycles());
                    if (mask & Z_POS)
                        p->Write8(item->GetPositionZ());
                    if (mask & BLINKING)
                        p->Write16(item->GetBlinking());
                    if (mask & FRAME)
                        p->Write16(item->GetFrame());
                    if (mask & LUA_ID)
                        p->Write16(item->GetLuaId());
                }

                void _SendPackets()
                {
                    std::map<size_t, Packet*>::iterator it = this->_buffers.begin();
                    std::map<size_t, Packet*>::iterator itEnd = this->_buffers.end();
                    for (; it != itEnd; ++it)
                    {
                        this->_game.GetPlayerManager().SendPacket(*it->second, it->first);
                        delete it->second;
                    }
                    this->_buffers.clear();
                    if (this->_packet != 0)
                    {
                        this->_game.GetPlayerManager().SendPacket(*this->_packet, 0);
                        delete this->_packet;
                        this->_packet = 0;
                    }
                }

                Packet* _GetPacketOfPlayer(uint16_t playerId)
                {
                    if (playerId == 0)
                    {
                        if (this->_packet == 0)
                        {
                            this->_packet = new Packet();
                            this->_packet->Write8(Packet::IN_GAME);
                            this->_packet->WriteFloat(this->_game.GetElapsedTime());
                        }
                        else if (this->_packet->GetSize() >= MAXPACKETSIZE)
                        {
                            this->_game.GetPlayerManager().SendPacket(*this->_packet, playerId);
                            Log::D("Sending packet splitted to " + String(this->_packet->GetSize()) + " bytes.");
                            delete this->_packet;
                            this->_packet = new Packet();
                            this->_packet->Write8(Packet::IN_GAME);
                            this->_packet->WriteFloat(this->_game.GetElapsedTime());
                        }
                        return this->_packet;
                    }
                    try
                    {
                        if (this->_game.GetPlayerManager().GetPlayer(playerId).IsDisabled())
                            return 0;
                        size_t a = playerId;
                        if (this->_buffers.count(a) == 0)
                        {
                            this->_buffers[a] = new Packet();
                            this->_buffers[a]->Write8(Packet::IN_GAME);
                            this->_buffers[a]->WriteFloat(this->_game.GetElapsedTime());
                        }
                        else if (this->_buffers[a]->GetSize() >= MAXPACKETSIZE)
                        {
                            this->_game.GetPlayerManager().SendPacket(*this->_buffers[a], a);
                            Log::D("Sending packet splitted to " + String(this->_buffers[a]->GetSize()) + " bytes.");
                            delete this->_buffers[a];
                            this->_buffers[a] = new Packet();
                            this->_buffers[a]->Write8(Packet::IN_GAME);
                            this->_buffers[a]->WriteFloat(this->_game.GetElapsedTime());
                        }
                        return this->_buffers[a];
                    }
                    catch (std::exception&)
                    {
                        return 0;
                    }
                }

                BasicGame<Entity, Player>& _game;
                std::map<size_t, Packet*> _buffers;
                uint32_t _itemId;
                std::map<Item*, uint32_t> _items;
                Packet* _packet;
        };

    }
}

#endif

