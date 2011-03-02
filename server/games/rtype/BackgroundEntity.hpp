#ifndef __BACKGROUNDENTITY_HPP__
#define __BACKGROUNDENTITY_HPP__

#include "GameEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class BackgroundEntity : public GameEntity
        {
            public:
                explicit BackgroundEntity(Game& game, uint16_t resourceId, int width, bool fillScreen, int yOffset = 0, float speed = -15);
                ~BackgroundEntity(void);
                virtual void Run(float time);

            private:
                uint16_t _resourceId;
                int _width;
                int _yOffset;
                float _speed;
                float _nextSpawn;
        };

    }
}

#endif

