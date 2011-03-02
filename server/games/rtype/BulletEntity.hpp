
#ifndef BULLETENTITY_HPP_
# define BULLETENTITY_HPP_

#include "GameEntity.hpp"
#include "Item.hpp"
#include "FriendlyDamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class BulletEntity : public GameEntity
        {
            friend class Decorator;
        protected:
            explicit BulletEntity(Game& game,
                                  InteractionPtr const& damage,
                                  int spriteLocalId,
                                  int explosionLocalId,
                                  float posX,
                                  float posY,
                                  float speedX,
                                  float speedY,
                                  float radius,
                                  float explosionRadius,
                                  uint16_t playerId);

        public:
            virtual ~BulletEntity(void);

            virtual void Run(float time);

            // Interactions (bullet default behavior, can be overwritten)
            virtual bool Interact(WallInteraction& interaction);

        protected:
            void _Explode(bool damage = false);
            virtual void _ExplodeEffects(void);

            Item _sprite;
            int _explosionLocalId;
            InteractionPtr _damage;
            float _radius;
            float _explosionRadius;
        };

    }
}

#endif // !BULLETENTITY_HPP_
