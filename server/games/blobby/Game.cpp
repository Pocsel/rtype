
#include "Game.hpp"
#include "Resources.hpp"
#include "ManagerEntity.hpp"
#include "AnimationResourceInfo.hpp"

namespace Gmgp
{
    namespace Server
    {

        Game::Game() :
            Common2Game<Entity, Game, PlayerEntity, ManagerEntity, 40, 320, 240, 2>("Blobby")
        {
        }

        Game::~Game()
        {
        }

        void Game::_InitializeResources()
        {
            this->_InitializeCommon2Resources();
            this->_Load(Resources::BACKGROUND, new AnimationResourceInfo("blobby/data/animations/background.png", 1, 0, false));
            this->_Load(Resources::P1_ICON, new AnimationResourceInfo("blobby/data/animations/p1_icon.png", 1, 0, false));
            this->_Load(Resources::P2_ICON, new AnimationResourceInfo("blobby/data/animations/p2_icon.png", 1, 0, false));
            this->_Load(Resources::PLAYER1, new AnimationResourceInfo("blobby/data/animations/p1.png", 1, 0, false));
            this->_Load(Resources::PLAYER2, new AnimationResourceInfo("blobby/data/animations/p2.png", 1, 0, false));
            this->_Load(Resources::BALL, new AnimationResourceInfo("blobby/data/animations/ball.png", 1, 0, false));
            this->_Load(Resources::BAR, new AnimationResourceInfo("blobby/data/animations/bar.png", 1, 0, false));
        }

        ManagerEntity* Game::_CreateManagerEntity()
        {
            return new ManagerEntity(*this);
        }

    }
}

