#include "Game.hpp"
#include "BackgroundEntity.hpp"
#include "ScoreBoardEntity.hpp"
#include "AnimationResourceInfo.hpp"
#include "SoundResourceInfo.hpp"

namespace Gmgp
{
    namespace Server
    {

        Game::Game(void)
            : BasicGame<Entity, Player>("ULTIMATE CHICKEN DEFENDER 5", 50, 640, 480)
        {
        }

        Game::~Game(void)
        {
        }

        void Game::_PreRun(void)
        {
            this->_background = new BackgroundEntity(*this);
            this->_scoreBoard = new ScoreBoardEntity(*this);
        }

        void Game::_PostRun(void)
        {
            delete this->_background;
            delete this->_scoreBoard;
        }

        void Game::_InitializeResources(void)
        {
            this->GetResourceManager().RegisterResource(CHICKEN1_LEFT, new AnimationResourceInfo("chicken/data/animations/chicken1l.png", 2, 99, false));
            this->GetResourceManager().RegisterResource(CHICKEN2_LEFT, new AnimationResourceInfo("chicken/data/animations/chicken2l.png", 2, 99, false));
            this->GetResourceManager().RegisterResource(CHICKEN3_LEFT, new AnimationResourceInfo("chicken/data/animations/chicken3l.png", 2, 184, false));
            this->GetResourceManager().RegisterResource(CHICKEN4_LEFT, new AnimationResourceInfo("chicken/data/animations/chicken4l.png", 2, 184, false));
            this->GetResourceManager().RegisterResource(CHICKEN1_RIGHT, new AnimationResourceInfo("chicken/data/animations/chicken1r.png", 2, 99, false));
            this->GetResourceManager().RegisterResource(CHICKEN2_RIGHT, new AnimationResourceInfo("chicken/data/animations/chicken2r.png", 2, 99, false));
            this->GetResourceManager().RegisterResource(CHICKEN3_RIGHT, new AnimationResourceInfo("chicken/data/animations/chicken3r.png", 2, 184, false));
            this->GetResourceManager().RegisterResource(CHICKEN4_RIGHT, new AnimationResourceInfo("chicken/data/animations/chicken4r.png", 2, 184, false));
            this->GetResourceManager().RegisterResource(CHICKEN1_DEATH, new AnimationResourceInfo("chicken/data/animations/chicken1d.png", 5, 88, false));
            this->GetResourceManager().RegisterResource(CHICKEN2_DEATH, new AnimationResourceInfo("chicken/data/animations/chicken2d.png", 5, 88, false));
            this->GetResourceManager().RegisterResource(CHICKEN3_DEATH, new AnimationResourceInfo("chicken/data/animations/chicken3d.png", 5, 162, false));
            this->GetResourceManager().RegisterResource(CHICKEN4_DEATH, new AnimationResourceInfo("chicken/data/animations/chicken4d.png", 5, 162, false));
            this->GetResourceManager().RegisterResource(CHICKEN_BLOOD1, new AnimationResourceInfo("chicken/data/animations/chickenb1.png", 3, 88, false));
            this->GetResourceManager().RegisterResource(CHICKEN_BLOOD2, new AnimationResourceInfo("chicken/data/animations/chickenb2.png", 3, 88, false));
            this->GetResourceManager().RegisterResource(AIM1, new AnimationResourceInfo("chicken/data/animations/aim1.png", 8, 94, false));
            this->GetResourceManager().RegisterResource(IMPACT1, new AnimationResourceInfo("chicken/data/animations/impact1.png", 1, 0, false));
            this->GetResourceManager().RegisterResource(BIG_EXPLOSION, new AnimationResourceInfo("chicken/data/animations/bigexplosion999.png", 19, 73, false));
            this->GetResourceManager().RegisterResource(BACKGROUND_KFC, new AnimationResourceInfo("chicken/data/animations/background_kfc.png", 1, 0, false));
            this->GetResourceManager().RegisterResource(FONT, new AnimationResourceInfo("common/data/animations/font1.png", 94, 0, false));

            this->GetResourceManager().RegisterResource(MUSIC, new SoundResourceInfo("chicken/data/sounds/slayertrash-cartoon_netcrunk.ogg", true));
            this->GetResourceManager().RegisterResource(SOUND_DEATH, new SoundResourceInfo("chicken/data/sounds/chicken_death.ogg", false));
            this->GetResourceManager().RegisterResource(SOUND_WEAPON, new SoundResourceInfo("chicken/data/sounds/deagle-1.ogg", false));
            this->GetResourceManager().RegisterResource(SOUND_EXPLOSION, new SoundResourceInfo("chicken/data/sounds/awp1.ogg", false));
        }

    }
}
