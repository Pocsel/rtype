#include "TimerEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        TimerEntity::TimerEntity(Game& game) :
            GameEntity(game, "Timer"), _running(true), _nextUpdate(0), _secs(0)
        {
            this->_prefix = new TextEntity<GameEntity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7);
            this->_prefix->SetText("Endurance:");
            this->_prefix->SetPosition(95, Game::HEIGHT + 8, 250);
            this->_timer = new TextEntity<GameEntity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7);
        }

        TimerEntity::~TimerEntity()
        {
            delete this->_prefix;
            delete this->_timer;
        }

        void TimerEntity::Run(float time)
        {
            if (time >= this->_nextUpdate && this->_running)
            {
                this->_nextUpdate = time + 1;
                ++this->_secs;
                String minutes(this->_secs / 60);
                if (minutes.size() <= 1)
                    minutes = "0" + minutes;
                String sec(this->_secs % 60);
                if (sec.size() <= 1)
                    sec = "0" + sec;
                this->_timer->SetText(minutes + ":" + sec);
                this->_timer->SetPosition(170, Game::HEIGHT + 8, 250);
            }
        }

        void TimerEntity::Stop()
        {
            this->_running = false;
        }

        void TimerEntity::Continue()
        {
            this->_running = true;
        }

    }
}


