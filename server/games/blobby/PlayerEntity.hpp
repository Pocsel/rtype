
#ifndef PLAYERENTITY_HPP_
# define PLAYERENTITY_HPP_

#include "Common2PlayerEntity.hpp"
#include "Entity.hpp"
#include "String.hpp"
#include "Item.hpp"
#include "Player.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class PlayerEntity
            : public Common2PlayerEntity<Entity, Game, PlayerEntity>
        {
        public:
            enum
            {
                HEIGHT = 40,
                WIDTH = 30,
            };
        public:
            explicit PlayerEntity(Game& game, uint16_t playerId, String const& nick);
            virtual ~PlayerEntity();

            virtual void Run(float time);

            virtual bool IsAlive();

            void Spawn(bool p1);
            void Die();
        private:
            void _DoStuff(Player& player);

            Item* _player;
            bool _p1;
        };

    }
}

#endif // !PLAYERENTITY_HPP_
