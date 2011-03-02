
#ifndef GAME_HPP_
# define GAME_HPP_

#include "Common2Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Entity;
        class PlayerEntity;
        class ManagerEntity;

        class Game :
            public Common2Game<Entity, Game, PlayerEntity, ManagerEntity, 40, 320, 240, 2>
        {
        public:
            explicit Game();
            virtual ~Game();

        protected:
            virtual void _InitializeResources();

            virtual ManagerEntity* _CreateManagerEntity();
        };

    }
}

#endif // !GAME_HPP_
