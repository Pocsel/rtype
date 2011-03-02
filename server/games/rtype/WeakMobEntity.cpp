
#include "WeakMobEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "EnemyBulletEntity.hpp"
#include "EnemyDamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        WeakMobEntity::WeakMobEntity(Game& game, float y)
            : MonsterEntity(game,
                            Resources::MONSTER1,
                            Resources::EXPLOSION2,
                            y,    //y
                            -70 - (static_cast<int>(y) % 7) * 4.789f, //speedX
                            16,   //w
                            20,   //h
                            10,   //life
                            200),  //score
            _nextDirectionTime(game.GetElapsedTime() + 0.4f)
        {
            this->_sprite.SetAccelY((static_cast<int>(y) % 4) >= 2 ? -200.0f : 200.0f);
        }

        WeakMobEntity::~WeakMobEntity()
        {
        }


        void WeakMobEntity::_Run(float time)
        {
            if (time > this->_nextDirectionTime)
            {
                this->_nextDirectionTime += 0.8f;
                this->_sprite.SetAccelY(this->_sprite.GetAccelY() * -1);
                this->_sprite.SetSpeedY(this->_sprite.GetSpeedY());
                this->_sprite.SetPositionY(this->_sprite.GetPositionY());
            }
        }

    }
}

