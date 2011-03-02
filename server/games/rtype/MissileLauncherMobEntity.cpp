#include "MissileLauncherMobEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "EnemyBulletEntity.hpp"
#include "EnemyDamageInteraction.hpp"
#include "MissileEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        MissileLauncherMobEntity::MissileLauncherMobEntity(Game& game, float y, bool move) :
            MonsterEntity(game,
                    Resources::MISSILE_LAUNCHER_UP,
                    Resources::EXPLOSION2,
                    y, //y
                    -Game::WALL_SPEED, //speedX
                    30, //w
                    22, //h
                    50, //life
                    1000), //score
            _missiles(0), _state(MOVING), _timeSave(game.GetElapsedTime()), _move(move)
        {
            if (this->_move)
            {
                this->_sprite.SetSpeedX(-SPEED);
                this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::MISSILE_LAUNCHER_LEFT));
            }
            else
                this->_sprite.SetFrame(1);
        }

        MissileLauncherMobEntity::~MissileLauncherMobEntity()
        {
        }

        void MissileLauncherMobEntity::_Run(float time)
        {
            if (this->_state == MOVING)
            {
                if (time - this->_timeSave >= 1.5)
                {
                    this->_state = FIRING;
                    this->_sprite.SetSpeedX(-Game::WALL_SPEED);
                    this->_sprite.SetPositionX(this->_sprite.GetPositionX());
                    this->_sprite.SetPositionY(this->_sprite.GetPositionY() - 4);
                    this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::MISSILE_LAUNCHER_UP));
                    this->_sprite.SetFrame(1);
                    this->_timeSave = time;
                }
            }
            else
            {
                if (this->_missiles == 0)
                {
                    if (time - this->_timeSave >= 0.3)
                    {
                        this->_sprite.SetFrame(0);
                        new MissileEntity(this->_game, this->_sprite.GetPositionX() + 6, this->_sprite.GetPositionY() - 8, MissileEntity::UP);
                        ++this->_missiles;
                    }
                }
                if (this->_missiles == 1)
                {
                    if (time - this->_timeSave >= 0.7)
                    {
                        new MissileEntity(this->_game, this->_sprite.GetPositionX() + 6, this->_sprite.GetPositionY() - 8, MissileEntity::CENTER);
                        ++this->_missiles;
                    }
                }
                if (this->_missiles == 2)
                {
                    if (time - this->_timeSave >= 1.1)
                    {
                        new MissileEntity(this->_game, this->_sprite.GetPositionX() + 6, this->_sprite.GetPositionY() - 8, MissileEntity::DOWN);
                        ++this->_missiles;
                    }
                }
                if (time - this->_timeSave >= 1.5)
                {
                    this->_state = MOVING;
                    if (this->_move)
                    {
                        this->_sprite.SetSpeedX(-SPEED);
                        this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::MISSILE_LAUNCHER_LEFT));
                    }
                    else
                        this->_sprite.SetFrame(1);
                    this->_sprite.SetPositionX(this->_sprite.GetPositionX());
                    this->_sprite.SetPositionY(this->_sprite.GetPositionY() + 4);
                    this->_missiles = 0;
                    this->_timeSave = time;
                }
            }
        }

    }
}
