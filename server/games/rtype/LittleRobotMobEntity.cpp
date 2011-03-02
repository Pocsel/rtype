
#include <cmath>

#include "LittleRobotMobEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "EnemyBulletEntity.hpp"
#include "EnemyDamageInteraction.hpp"
#include "Utils.hpp"

namespace Gmgp
{
    namespace Server
    {

        LittleRobotMobEntity::LittleRobotMobEntity(Game& game, float y, bool reverse)
            : MonsterEntity(game,
                            (reverse ? Resources::MONSTER2_REVERSE : Resources::MONSTER2),
                            Resources::EXPLOSION2,
                            y,    //y
                            (reverse ? 1 : -1) * (30 - (static_cast<int>(y) % 12) * 1.4712f), //speedX
                            26,   //w
                            27,   //h
                            20,   //life
                            400),  //score
            _nextBulletTime(0),
            _nextMoveTime(game.GetElapsedTime() + 1.1454f)
        {
            this->_RandomizeVerticalSpeed();
        }

        LittleRobotMobEntity::~LittleRobotMobEntity()
        {
        }

        void LittleRobotMobEntity::_Run(float time)
        {
            if (time > this->_nextBulletTime)
            {
                this->_ShootBullet();
                this->_nextBulletTime = time + 0.9123f;
            }

            if (time > this->_nextMoveTime)
            {
                this->_RandomizeVerticalSpeed();
                this->_nextMoveTime = time + (static_cast<int>(this->_sprite.GetPositionX()) % 25 + static_cast<int>(this->_sprite.GetPositionY()) % 28) * 0.03789f;
            }
        }

        void LittleRobotMobEntity::_RandomizeVerticalSpeed(void)
        {
            if (this->_sprite.GetPositionY() < Game::HEIGHT / 5)
                this->_sprite.SetSpeedY(0.0f + static_cast<int>(this->_sprite.GetPositionY()) % 35);
            else if (this->_sprite.GetPositionY() > Game::HEIGHT * 4/5)
                this->_sprite.SetSpeedY(-static_cast<int>(this->_sprite.GetPositionY()) % 35);
            else
                this->_sprite.SetSpeedY(-40.0f + static_cast<int>(this->_sprite.GetPositionY()) % 80);
            this->_sprite.SetPositionY(this->_sprite.GetPositionY());
        }

        void LittleRobotMobEntity::_ShootBullet(void)
        {
            float speedX;
            float speedY;

            Point pos = this->GetPosition();
            ShipEntity* nearestPlayer;
            if ((nearestPlayer = Utils::GetNearestShipEntity(this->_game, pos)) != 0)
            {
                pos = nearestPlayer->GetPosition() - pos;
                pos.x -= 6;
                float num = 1.0f / ::sqrtf((pos.x * pos.x) + (pos.y * pos.y));
                speedX = 80 * pos.x * num;
                speedY = 80 * pos.y * num;
            }
            else
            {
                speedX = -80;
                speedY = this->_game.R() * 30;
            }

            new EnemyBulletEntity(this->_game,
                    InteractionPtr(new EnemyDamageInteraction(10, this)),
                    Resources::BULLET2,
                    Resources::EXPLOSION3,
                    this->_sprite.GetPositionX() + 8,
                    this->_sprite.GetPositionY(),
                    speedX,
                    speedY,
                    3,
                    12,
                    this->GetPlayerId()
                    );
        }
    }
}


