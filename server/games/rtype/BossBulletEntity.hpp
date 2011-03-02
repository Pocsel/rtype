
#ifndef BOSSBULLETENTITY_HPP_
# define BOSSBULLETENTITY_HPP_

#include "BulletEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ShipInteraction;
        class Game;

        class BossBulletEntity : public BulletEntity
        {
        public:
            explicit BossBulletEntity(Game& game,
                                       InteractionPtr const& damage,
                                       int spriteLocalId,
                                       int explosionLocalId,
                                       float posX,
                                       float posY,
                                       float speedX,
                                       float speedY,
                                       float radius,
                                       float explosionRadius,
                                       uint16_t playerId = 0);
            ~BossBulletEntity(void);

            // Interactions
            virtual bool Interact(ShipInteraction& interaction);
            virtual bool Interact(ShieldInteraction& interaction);
            virtual bool Interact(WallInteraction& interaction);

        private:
            float _decorTime;
        };

    }
}

#endif // !BOSSBULLETENTITY_HPP_
