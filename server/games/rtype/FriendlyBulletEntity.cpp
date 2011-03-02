
#include "FriendlyBulletEntity.hpp"
#include "MonsterInteraction.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        FriendlyBulletEntity::FriendlyBulletEntity(Game& game,
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
            _damage(0)
        {
        }

        FriendlyBulletEntity::~FriendlyBulletEntity(void)
        {
        }

        void FriendlyBulletEntity::SetDamage(int damage)
        {
            this->_damage = damage;
        }

        bool FriendlyBulletEntity::Interact(MonsterInteraction& interaction)
        {
            this->_damage -= interaction.Damage(this->_damage, this->GetPlayerId());
            if (this->_damage <= 0)
            {
                this->_Explode(true);
                delete this;
                return false;
            }
            this->_Explode(false);
            return true;
        }

    }
}
