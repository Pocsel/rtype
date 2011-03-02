#include "Game.hpp"
#include "AnimationResourceInfo.hpp"
#include "SoundResourceInfo.hpp"

namespace Gmgp
{
    namespace Server
    {

        Game::Game() :
            BasicGame<Entity, Player>("MainMenu", 50, 320, 240)
        {
            Log::I("MainMenu created.");
        }

        Game::~Game()
        {
            Log::I("MainMenu destroyed.");
        }

        void Game::_InitializeResources()
        {
            this->GetResourceManager().RegisterResource(Game::FONT, new AnimationResourceInfo("common/data/animations/font1.png", 94, 0, false));
            this->GetResourceManager().RegisterResource(Game::BG, new AnimationResourceInfo("mainmenu/data/animations/bg.png", 1, 0, false));
            this->GetResourceManager().RegisterResource(Game::PLUGIN, new AnimationResourceInfo("mainmenu/data/animations/plugin.png", 1, 0, false));
            this->GetResourceManager().RegisterResource(Game::PLUGIN_DISABLED, new AnimationResourceInfo("mainmenu/data/animations/plugin_disabled.png", 1, 0, false));
            this->GetResourceManager().RegisterResource(Game::CURSOR, new AnimationResourceInfo("mainmenu/data/animations/cursor.png", 1, 0, false));
        }

    }
}

