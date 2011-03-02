#ifndef __MONSTERENTITY_HPP__
#define __MONSTERENTITY_HPP__

#include "GameEntity.hpp"
#include "Item.hpp"
#include "Point.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MonsterEntity : public GameEntity
        {
            friend class Decorator;
        protected:
            explicit MonsterEntity(Game& game,
                                   int spriteId,
                                   int explosionId,
                                   float y,
                                   float speedX = -60,
                                   float w = 10,
                                   float h = 10,
                                   int life = 1,
                                   int score = 1
                                   );

        public:
            virtual ~MonsterEntity();

            virtual void GenerateInteractions(float time);
            virtual void Run(float time);

            // Interactions
            virtual bool Interact(FriendlyDamageInteraction& interaction);
            virtual bool Interact(ShipInteraction& interaction);
            virtual bool Interact(WallInteraction& interaction);

            Point GetPosition(void) const;

        protected:
            virtual void _Run(float time);

            bool _Damage(int damage, uint16_t playerId);

            Item _sprite;
            InteractionPtr _interaction;

            float _width;
            float _height;

            int _explosionId;
            int _score;
        };

    }
}

#endif

