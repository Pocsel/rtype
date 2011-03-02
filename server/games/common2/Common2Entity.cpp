#include "Common2Entity.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, typename G>
            Common2Entity<E, G>::Common2Entity(G& game, String const& name, uint16_t playerId /* = 0 */) :
                _game(game), _name(name), _playerId(playerId)
        {
            this->_game.GetEntityManager().RegisterEntity(reinterpret_cast<E*>(this));
        }

        template<typename E, typename G>
            Common2Entity<E, G>::~Common2Entity()
            {
            this->_game.GetEntityManager().UnregisterEntity(reinterpret_cast<E*>(this));
            }

        template<typename E, typename G>
            void Common2Entity<E, G>::GenerateInteractions(float)
            {
            }

        template<typename E, typename G>
            void Common2Entity<E, G>::Run(float)
            {
            }

        template<typename E, typename G>
            uint16_t Common2Entity<E, G>::GetPlayerId() const
            {
                return this->_playerId;
            }

        template<typename E, typename G>
            void Common2Entity<E, G>::SetPlayerId(uint16_t playerId)
            {
                this->_playerId = playerId;
            }

        template<typename E, typename G>
            void Common2Entity<E, G>::SetName(String const& name)
            {
                this->_name = name;
            }

        template<typename E, typename G>
            String const& Common2Entity<E, G>::GetName() const
            {
                return this->_name;
            }

    }
}

