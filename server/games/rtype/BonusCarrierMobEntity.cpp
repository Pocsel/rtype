
#include "BonusCarrierMobEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "EnemyBulletEntity.hpp"
#include "EnemyDamageInteraction.hpp"
#include "BonusEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        BonusCarrierMobEntity::BonusCarrierMobEntity(Game& game, float y, int bonusType, int bonusLocalId)
            : MonsterEntity(game,
                            Resources::BONUS_CARRIER,
                            Resources::EXPLOSION2,
                            y,    //y
                            -42 - (static_cast<int>(y) % 7) * 4.789f, //speedX
                            20,   //w
                            17,   //h
                            10,   //life
                            200),  //score
            _nextMoveTime(game.GetElapsedTime() + 1.1454f),
            _bonusType(bonusType),
            _bonusLocalId(bonusLocalId)

        {
            this->_RandomizeVerticalSpeed();
        }

        BonusCarrierMobEntity::~BonusCarrierMobEntity()
        {
            new BonusEntity(this->_game, this->_bonusType, this->_bonusLocalId, this->_sprite.GetPositionX(), this->_sprite.GetPositionY());
        }

        void BonusCarrierMobEntity::_Run(float time)
        {
            if (time > this->_nextMoveTime)
            {
                this->_RandomizeVerticalSpeed();
                this->_nextMoveTime = time + (static_cast<int>(this->_sprite.GetPositionX()) % 25 + static_cast<int>(this->_sprite.GetPositionY()) % 28) * 0.03789f;
            }
        }

        void BonusCarrierMobEntity::_RandomizeVerticalSpeed(void)
        {
            if (this->_sprite.GetPositionY() < Game::HEIGHT / 5)
                this->_sprite.SetSpeedY(0.0f + static_cast<int>(this->_sprite.GetPositionY()) % 35);
            else if (this->_sprite.GetPositionY() > Game::HEIGHT * 4/5)
                this->_sprite.SetSpeedY(-1.0f * (static_cast<int>(this->_sprite.GetPositionY()) % 35));
            else
                this->_sprite.SetSpeedY(-40.0f + static_cast<int>(this->_sprite.GetPositionY()) % 80);
            this->_sprite.SetPositionY(this->_sprite.GetPositionY());
        }

    }
}

