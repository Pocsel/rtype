#ifndef __MAINMENUENTITY_HPP__
#define __MAINMENUENTITY_HPP__

#include <map>
#include "MainMenuEntity.hpp"
#include "ButtonEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MainMenuEntity : public MenuEntity
        {
            public:
                explicit MainMenuEntity(MainGame& game, uint16_t playerId);
                ~MainMenuEntity();
                void Run(float time);
            private:
//                void _DisablePlayer();
                void _UpdateGameList();
                void _RemoveGameList();
                Item _background;
                ButtonEntity* _createGame;
                ButtonEntity* _modeButton;
                size_t _nbGames;
                std::map<uint16_t, ButtonEntity*> _list;
                int _mode;
        };

    }
}

#endif

