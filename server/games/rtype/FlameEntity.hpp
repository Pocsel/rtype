
#ifndef FLAMEENTITY_HPP_
# define FLAMEENTITY_HPP_


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

        class FlameEntity : public FriendlyBulletEntity
        {
        private:
            enum Constant
            {
                SPEED = 200,
                MAX_BOING = 4,
            };


        public:
            explicit FlameEntity(Game& game,
                                 bool up,
                                      float posX,
                                      float posY,
                                      uint16_t playerId = 0);
            virtual ~FlameEntity(void);

            // Interactions
            virtual bool Interact(WallInteraction& interaction);

        private:
            virtual void _ExplodeEffects(void);

            bool _up;
            int _boingCount;
        };

    }
}

#endif // !FLAMEENTITY_HPP_
