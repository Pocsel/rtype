
#ifndef BOMBENTITY_HPP_
# define BOMBENTITY_HPP_

#include "Entity.hpp"
#include "Item.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        class BombInteraction;

        class BombEntity : public Entity
        {
        private:
            enum
            {
                TIME = 4,
            };

            enum
            {
                CENTER = Resources::EXPLOSION_CENTER,
                VERTICAL = Resources::EXPLOSION_VERTICAL,
                HORIZONTAL = Resources::EXPLOSION_HORIZONTAL,
                UP = Resources::EXPLOSION_UP,
                DOWN = Resources::EXPLOSION_DOWN,
                LEFT = Resources::EXPLOSION_LEFT,
                RIGHT = Resources::EXPLOSION_RIGHT,
            };

        public:
            BombEntity(Game& game, uint16_t playerId, int power, float x, float y);
            virtual ~BombEntity(void);

            virtual void Run(float time);

            virtual bool Interact(BombInteraction& interaction);

        private:
            void _Explode(void);
            bool _TryCase(int id, float x, float y);
            void _PutExplosion(int id, float x, float y, bool dispSprite);

            Item _sprite;
            int _power;
            float _time;
            InteractionPtr _bombInteraction;
        };

    }
}

#endif // !BOMBENTITY_HPP_
