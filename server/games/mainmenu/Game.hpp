#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "BasicGame.hpp"
#include "Clock.hpp"
#include "Entity.hpp"
#include "Player.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game : public BasicGame<Entity, Player>
        {
        public:
            enum
            {
                FONT,
                BG,
                PLUGIN,
                PLUGIN_DISABLED,
                CURSOR
            };
            explicit Game();
            ~Game();
        protected:
            virtual void _InitializeResources();
        };

    }
}

#endif

