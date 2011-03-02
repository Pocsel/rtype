#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "BasicPlayer.hpp"
#include "Item.hpp"
#include "MenuEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Entity;
        class Game;
        template<typename Entity, typename Player> class BasicGame;
        class ITcpSocketProxy;

        class Player :
            public BasicPlayer
        {
            public:
                explicit Player(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<Entity, Player>& game);
                ~Player();

            private:
                Game& _game;
                MenuEntity* _menu;
        };

    }
}

#endif

