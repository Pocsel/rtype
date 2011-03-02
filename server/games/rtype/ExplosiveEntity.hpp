
#ifndef EXPLOSIVEENTITY_HPP_
# define EXPLOSIVEENTITY_HPP_

#include <vector>

#include "GameEntity.hpp"
#include "Item.hpp"
#include "FriendlyBulletEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;
        class WallInteraction;

        class ExplosiveEntity : public FriendlyBulletEntity
        {
        private:
            enum Constant
            {
                SPEED = 50,
                TIME = 2,
            };

        public:
            explicit ExplosiveEntity(Game& game,
                                     bool forward,
                                     float posX,
                                     float posY,
                                     uint16_t playerId = 0);
            virtual ~ExplosiveEntity(void);

            virtual void Run(float time);
            virtual bool Interact(WallInteraction& interaction);

        private:
            virtual void _ExplodeEffects(void);
            float _deathTime;
        };

    }
}

#endif // !EXPLOSIVEENTITY_HPP_
