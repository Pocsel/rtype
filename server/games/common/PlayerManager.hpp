#ifndef __PLAYERMANAGER_HPP__
#define __PLAYERMANAGER_HPP__

#include <list>
#include <map>

#include "NonCopyable.hpp"
#include "Packet.hpp"
#include "Mutex.hpp"
#include "ScopeLock.hpp"
#include "Log.hpp"
#include "ITcpSocketProxy.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename Entity, typename Player>
            class PlayerManager :
                private b00st::NonCopyable
        {
        private:
            struct PlayerMetadata
            {
                size_t id;
                String nick;
                ITcpSocketProxy* socketProxy;
            };

        public:

            PlayerManager(BasicGame<Entity, Player>& game) : _game(game)
            {
            }

            ~PlayerManager()
            {
                for (typename std::list<PlayerMetadata*>::iterator it = this->_newPlayers.begin(), ite = this->_newPlayers.end() ; it != ite ; ++it)
                {
                    delete (*it)->socketProxy;
                    delete *it;
                }
                for (typename std::map<size_t, Player*>::iterator it = this->_players.begin(), itEnd = this->_players.end() ; it != itEnd ; ++it)
                {
                    ITcpSocketProxy* s = it->second->GetSocketProxy();
                    delete it->second;
                    delete s;
                }
            }

        public:
            void FlushEvents()
            {
                //reset clicks
                typename std::map<size_t, Player*>::iterator it = this->_players.begin();
                typename std::map<size_t, Player*>::iterator itEnd = this->_players.end();
                for (; it != itEnd; ++it)
                    it->second->ResetClicks();

                // add new
                ScopeLock lock(this->_mutex);

                typename std::list<PlayerMetadata*>::iterator ait = this->_newPlayers.begin();
                typename std::list<PlayerMetadata*>::iterator aitEnd = this->_newPlayers.end();
                for (; ait != aitEnd; ++ait)
                {
                    if (!this->HasPlayer((*ait)->id))
                    {
                        Player* michel = new Player((*ait)->id, (*ait)->nick, (*ait)->socketProxy, this->_game);
                        this->_players[(*ait)->id] = michel;

                        Packet p;
                        p.Write8(Packet::WATCH_THIS_OUT);
                        p.Write16(this->_game.GetWidth());
                        p.Write16(this->_game.GetHeight());
                        p.Write16(0); // unused port
                        michel->SendPacket(p);
                        this->_game.GetItemManager().RefreshPlayer((*ait)->id);
                    }
                    delete *ait;
                }
                this->_newPlayers.clear();
            }

            std::list<uint16_t> GetPlayerIdList() const
            {
                std::list<uint16_t> ret;
                typename std::map<size_t, Player*>::const_iterator it = this->_players.begin();
                typename std::map<size_t, Player*>::const_iterator itEnd = this->_players.end();
                for (; it != itEnd; ++it)
                    ret.push_back(it->first);
                return ret;
            }

            bool Ping(uint16_t playerId)
            {
                if (this->_players.count(playerId) != 1)
                {
                    Log::W(this->_game.GetName() + ": Could not ping player " + String(playerId) + ": player not found.");
                    return true;
                }
                return this->_players[playerId]->Ping();
            }

            bool SendPacket(Packet const& packet, uint16_t id)
            {
                if (id == 0)
                {
                    typename std::map<size_t, Player*>::iterator it = this->_players.begin();
                    typename std::map<size_t, Player*>::iterator itEnd = this->_players.end();
                    for (; it != itEnd; ++it)
                        if (!it->second->IsDisabled())
                            it->second->SendPacket(packet);
                    return true;
                }
                if (this->_players.count(id) != 1)
                {
                    Log::W(this->_game.GetName() + ": Could not send IN_GAME packet to player " + String(id) + ": player not found.");
                    return false;
                }
                this->_players[id]->SendPacket(packet);
                return true;
            }

            void AddPlayer(size_t id, String const& nick, ITcpSocketProxy* socketProxy)
            {
                PlayerMetadata* meta = new PlayerMetadata;
                meta->id = id;
                meta->nick = nick;
                meta->socketProxy = socketProxy;
                ScopeLock lock(this->_mutex);
                this->_newPlayers.push_back(meta);
            }

            bool HasPlayer(size_t id) const
            {
                return this->_players.count(id) == 1;
            }

            void RemovePlayer(size_t id)
            {
                typename std::list<PlayerMetadata*>::iterator it = this->_newPlayers.begin();
                typename std::list<PlayerMetadata*>::iterator itEnd = this->_newPlayers.end();
                while (it != itEnd)
                {
                    if ((*it)->id == id)
                    {
                        delete *it;
                        this->_newPlayers.erase(it++);
                    }
                    else
                        ++it;
                }

                if (this->HasPlayer(id))
                {
                    delete this->_players[id];
                    this->_players.erase(id);
                }
            }

            size_t GetNumberOfPlayers() const
            {
                return this->_players.size();
            }

            Player& GetPlayer(size_t id)
            {
                if (!this->HasPlayer(id))
                    throw std::runtime_error("player not found");
                return *this->_players[id];
            }

        private:
            BasicGame<Entity, Player>& _game;
            std::map<size_t, Player*> _players;
            std::list<PlayerMetadata*> _newPlayers;
            mutable Mutex _mutex;
        };

    }
}

#endif

