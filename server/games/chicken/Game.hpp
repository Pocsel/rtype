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

        class BackgroundEntity;
        class ScoreBoardEntity;

        class Game : public BasicGame<Entity, Player>
        {
        public:
            enum LocalResourceId
            {
                CHICKEN1_LEFT,
                CHICKEN2_LEFT,
                CHICKEN3_LEFT,
                CHICKEN4_LEFT,
                CHICKEN1_RIGHT,
                CHICKEN2_RIGHT,
                CHICKEN3_RIGHT,
                CHICKEN4_RIGHT,
                CHICKEN1_DEATH,
                CHICKEN2_DEATH,
                CHICKEN3_DEATH,
                CHICKEN4_DEATH,
                CHICKEN_BLOOD1,
                CHICKEN_BLOOD2,
                AIM1,
                IMPACT1,
                BIG_EXPLOSION,
                BACKGROUND_KFC,
                FONT,
                MUSIC,
                SOUND_DEATH,
                SOUND_WEAPON,
                SOUND_EXPLOSION,
            };

            explicit Game(void);
            ~Game(void);

        protected:
            virtual void _PreRun(void);
            virtual void _PostRun(void);
            virtual void _InitializeResources(void);

        private:
            BackgroundEntity* _background;
            ScoreBoardEntity* _scoreBoard;
        };

    }
}

#endif

