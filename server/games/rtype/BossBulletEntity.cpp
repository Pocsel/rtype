
#include "BossBulletEntity.hpp"
#include "MonsterInteraction.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        BossBulletEntity::BossBulletEntity(Game& game,
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
            : BulletEntity(game, damage, spriteLocalId, explosionLocalId, posX, posY, speedX, speedY, radius, explosionRadius, playerId),
            _decorTime(0)
        {
        }

        BossBulletEntity::~BossBulletEntity(void)
        {
        }

        bool BossBulletEntity::Interact(ShipInteraction&)
        {
            this->_Explode(true);
            delete this;
            return false;
        }

        bool BossBulletEntity::Interact(ShieldInteraction&)
        {
            if (this->_decorTime < this->_game.GetElapsedTime())
            {
                this->_Explode(false);
                this->_decorTime = this->_game.GetElapsedTime() + 0.1f;
            }
            return true;
        }

        bool BossBulletEntity::Interact(WallInteraction&)
        {
            return true;
        }
    }
}

