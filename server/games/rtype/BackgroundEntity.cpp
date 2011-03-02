#include "BackgroundEntity.hpp"
#include "Game.hpp"
#include "BgTileEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        BackgroundEntity::BackgroundEntity(Game& game, uint16_t resourceId, int width, bool fillScreen, int yOffset /* = 0 */, float speed /* = -15 */) :
            GameEntity(game, "Background"), _resourceId(resourceId), _width(width), _yOffset(yOffset), _speed(speed), _nextSpawn(0)
        {
            if (this->_speed == 0)
                this->_speed = -0.01f;
            if (this->_speed > 0)
                this->_speed *= -1;
            if (this->_width == 0)
                this->_width = 1;
            if (fillScreen)
            {
                for (int i = 0; i < Game::WIDTH / this->_width + 1; ++i)
                {
                    new BgTileEntity(this->_game,
                                     this->_resourceId,
                                     Game::WIDTH - this->_width * (i + 1) + this->_width / 2 + 1.0f, // x
                                     static_cast<float>(Game::HEIGHT / 2 + this->_yOffset), // y
                                     this->_width, // width
                                     3, // z
                                     this->_speed); // speed
                }
            }
        }

        BackgroundEntity::~BackgroundEntity()
        {
        }

        void BackgroundEntity::Run(float time)
        {
            if (this->_nextSpawn <= time)
            {
                new BgTileEntity(this->_game,
                                 this->_resourceId,
                                 Game::WIDTH + this->_width / 2, // x
                                 Game::HEIGHT / 2 + this->_yOffset, // y
                                 this->_width, // width
                                 3, // z
                                 this->_speed); // speed

                this->_nextSpawn = time + this->_width / this->_speed * -1 - 0.08f; // -80ms pour caler
            }
        }

    }
}

