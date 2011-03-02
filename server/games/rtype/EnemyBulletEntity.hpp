
#ifndef ENEMYBULLETENTITY_HPP_
# define ENEMYBULLETENTITY_HPP_

#include "BulletEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ShipInteraction;
        class Game;

        class EnemyBulletEntity : public BulletEntity
        {
        public:
            explicit EnemyBulletEntity(Game& game,
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
            ~EnemyBulletEntity(void);

            // Interactions
            virtual bool Interact(ShipInteraction& interaction);
            virtual bool Interact(ShieldInteraction& interaction);

        };

    }
}

#endif // !ENEMYBULLETENTITY_HPP_
