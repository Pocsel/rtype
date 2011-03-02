#ifndef __TIMERENTITY_HPP__
#define __TIMERENTITY_HPP__

#include "GameEntity.hpp"
#include "Item.hpp"
#include "TextEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class TimerEntity : public GameEntity
        {
            public:
                explicit TimerEntity(Game& game);
                ~TimerEntity(void);
                virtual void Run(float time);
                void Stop();
                void Continue();
            private:
                TextEntity<GameEntity, Game>* _prefix;
                TextEntity<GameEntity, Game>* _timer;
                bool _running;
                float _nextUpdate;
                size_t _secs;
        };

    }
}

#endif

