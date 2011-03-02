
#ifndef FRIENDLYBULLETENTITY_HPP_
# define FRIENDLYBULLETENTITY_HPP_

#include "BulletEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MonsterInteraction;
        class Game;

        class FriendlyBulletEntity : public BulletEntity
        {
        public:
            explicit FriendlyBulletEntity(Game& game,
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
            ~FriendlyBulletEntity(void);

            void SetDamage(int damage);

            // Interactions
            virtual bool Interact(MonsterInteraction& interaction);

        private:
            int _damage;
        };

    }
}

#endif // !FRIENDLYBULLETENTITY_HPP_
