#ifndef __MENUPLAYER_HPP__
#define __MENUPLAYER_HPP__

#include "BasicPlayer.hpp"
#include "Item.hpp"
#include "MainMenuEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MenuEntity;
        class MainGame;
        template<typename Entity, typename MenuPlayer> class BasicGame;
        class ITcpSocketProxy;

        class MenuPlayer :
            public BasicPlayer
        {
            public:
                explicit MenuPlayer(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<MenuEntity, MenuPlayer>& game);
                ~MenuPlayer();

            private:
                MainGame& _game;
                Item _cursor;
                MainMenuEntity* _mainMenu;
        };

    }
}

#endif

