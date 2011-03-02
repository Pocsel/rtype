#include <list>
#include "Common2PlayerEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, typename G, typename PE>
            Common2PlayerEntity<E, G, PE>::Common2PlayerEntity(G& game, uint16_t playerId, String const& nick) :
                E(game, "Player", playerId),
                _score(0),
                _nick(nick)
        {
            typename std::list<PE*> const& list = this->_game.GetListOfPlayers();
            bool found;
            for (this->_colorId = 0; this->_colorId < 1000; ++this->_colorId)
            {
                found = false;
                typename std::list<PE*>::const_iterator it = list.begin();
                typename std::list<PE*>::const_iterator itEnd = list.end();
                for (; it != itEnd && found == false; ++it)
                    if ((*it)->GetColorId() == this->_colorId)
                        found = true;
                if (!found)
                    break;
            }

            this->_game.RegisterPlayerEntity(reinterpret_cast<PE*>(this));
        }

        template<typename E, typename G, typename PE>
            Common2PlayerEntity<E, G, PE>::~Common2PlayerEntity()
            {
                this->_game.UnregisterPlayerEntity(reinterpret_cast<PE*>(this));
            }

        template<typename E, typename G, typename PE>
            String const& Common2PlayerEntity<E, G, PE>::GetNick() const
            {
                return this->_nick;
            }

        template<typename E, typename G, typename PE>
            int Common2PlayerEntity<E, G, PE>::GetColorId() const
            {
                return this->_colorId;
            }

        template<typename E, typename G, typename PE>
            bool Common2PlayerEntity<E, G, PE>::IsAlive() const
            {
                return true;
            }

        template<typename E, typename G, typename PE>
            void Common2PlayerEntity<E, G, PE>::LastAlive()
            {
            }

        template<typename E, typename G, typename PE>
            int Common2PlayerEntity<E, G, PE>::GetScore() const
            {
                return this->_score;
            }

        template<typename E, typename G, typename PE>
            void Common2PlayerEntity<E, G, PE>::AddScore(int s)
            {
                this->_score += s;
            }

    }
}

