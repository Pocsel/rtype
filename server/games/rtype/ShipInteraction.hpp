
#ifndef SHIPINTERACTION_HPP_
# define SHIPINTERACTION_HPP_

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ShipInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit ShipInteraction(uint16_t playerId, GameEntity *entity = 0);
            ~ShipInteraction(void);

            uint16_t GetPlayerId(void) const;

            virtual bool Interact(GameEntity& entity);

        private:
            uint16_t _playerId;
        };
    }
}

#endif // !SHIPINTERACTION_HPP_
