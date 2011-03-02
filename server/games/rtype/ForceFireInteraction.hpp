#ifndef __FORCEFIREINTERACTION_HPP__
#define __FORCEFIREINTERACTION_HPP__

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ForceFireInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit ForceFireInteraction(uint16_t playerId, GameEntity* entity);
            ~ForceFireInteraction();

            bool Interact(GameEntity& entity);

            uint16_t GetPlayerId() const;

        private:
            uint16_t _playerId;
        };

    }
}

#endif

