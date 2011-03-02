
#include "EnemyBulletEntity.hpp"
#include "MonsterInteraction.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        EnemyBulletEntity::EnemyBulletEntity(Game& game,
                                                   InteractionPtr const& damage,
                                                   int spriteLocalId,
                                                   int explosionLocalId,
                                                   float posX,
                                                   float posY,
                                                   float speedX,
                                                   float speedY,
                                                   float radius,
                                                   float explosionRadius,
                                                   uint16_t playerId /* = 0*/)
            : BulletEntity(game, damage, spriteLocalId, explosionLocalId, posX, posY, speedX, speedY, radius, explosionRadius, playerId)
        {
        }

        EnemyBulletEntity::~EnemyBulletEntity(void)
        {
        }

        bool EnemyBulletEntity::Interact(ShipInteraction&)
        {
            this->_Explode(true);
            delete this;
            return false;
        }

        bool EnemyBulletEntity::Interact(ShieldInteraction&)
        {
            this->_Explode(true);
            delete this;
            return false;
        }
    }
}
