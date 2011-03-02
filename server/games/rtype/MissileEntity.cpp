#include "MissileEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "EnemyDamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        MissileEntity::MissileEntity(Game& game, float x, float y, int type, float speedY /* = -200 */) :
            GameEntity(game, "Missile"), _sprite(this->_game.GetElapsedTime()), _type(type), _timeSave(game.GetElapsedTime()), _dirSet(false), _launched(false), _nbSmoke(0), _damage(new EnemyDamageInteraction(10, this)), _dead(false)
        {
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::ROTATING_MISSILE));
            this->_sprite.SetPositionX(x);
            this->_sprite.SetPositionY(y);
            //this->_sprite.SetSpeedX(-Game::WALL_SPEED);
            this->_sprite.SetSpeedY(speedY);
            this->_sprite.SetAccelY(190);
            this->_game.GetItemManager().AddItem(&this->_sprite);
        }

        MissileEntity::~MissileEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
        }

        void MissileEntity::Run(float time)
        {
            if (this->_sprite.GetPositionX() < -10 || this->_sprite.GetPositionY() > Game::FULLHEIGHT || this->_dead)
            {
                delete this;
                return;
            }
            this->_game.GetEntityManager().GetInteractionManager().Interact(*this,
                    Rect(this->_sprite.GetPositionX() - 4, this->_sprite.GetPositionY() - 2, 8, 4));
            if (this->_dirSet && this->_launched)
            {
                if (time - this->_timeSave < 0.08 || this->_nbSmoke > 9)
                    return;
                Item smoke;
                smoke.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::SMOKE));
                smoke.SetPositionX(this->_sprite.GetPositionX() + 2);
                smoke.SetPositionY(this->_sprite.GetPositionY());
                smoke.SetSpeedX(-Game::WALL_SPEED);
                smoke.SetLifeTimeCycles(1);
                smoke.SetPositionZ(130);
                this->_game.GetItemManager().SendItem(smoke);
                this->_timeSave = time;
                ++this->_nbSmoke;
                if (this->_nbSmoke == 8)
                    this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::MISSILE_CENTER));
            }
            else if (this->_dirSet)
            {
                if (time - this->_timeSave < 0.250)
                    return;
                this->_sprite.SetAccelX(0);
                this->_sprite.SetPositionX(this->_sprite.GetPositionX());
                this->_sprite.SetPositionY(this->_sprite.GetPositionY());
                if (this->_type == UP)
                {
                    this->_sprite.SetSpeedX(-250);
                    this->_sprite.SetSpeedY(-85);
                    this->_sprite.SetAccelY(80);
                }
                else if (this->_type == CENTER)
                {
                    this->_sprite.SetSpeedX(-290);
                    this->_sprite.SetSpeedY(0);
                    this->_sprite.SetAccelY(0);
                }
                else
                {
                    this->_sprite.SetSpeedX(-250);
                    this->_sprite.SetSpeedY(85);
                    this->_sprite.SetAccelY(-80);
                }
                Item ex;
                ex.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::MISSILE_FIRE));
                ex.SetPositionX(this->_sprite.GetPositionX() + 8);
                ex.SetPositionY(this->_sprite.GetPositionY());
                ex.SetLifeTimeCycles(1);
                ex.SetPositionZ(130);
                this->_game.GetItemManager().SendItem(ex);
                this->_launched = true;
                return;
            }
            else if (time - this->_timeSave > 1.4)
            {
                if (this->_type == UP)
                    this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::MISSILE_UP));
                else if (this->_type == CENTER)
                    this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::MISSILE_CENTER));
                else
                    this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::MISSILE_DOWN));
                this->_timeSave = time;
                this->_dirSet = true;
            }
        }

        void MissileEntity::_Explode(bool damage)
        {
            Item i;
            i.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::EXPLOSION7));
            i.SetPositionX(this->_sprite.GetPositionX());
            i.SetPositionY(this->_sprite.GetPositionY());
            i.SetSpeedX(-Game::WALL_SPEED);
            i.SetLifeTimeCycles(1);
            i.SetPositionZ(130);
            this->_dead = true;
            this->_game.GetItemManager().SendItem(i);
            if (damage)
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_damage,
                        Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 5));
        }

        bool MissileEntity::Interact(ShipInteraction&)
        {
            this->_Explode(true);
            return false;
        }

        bool MissileEntity::Interact(ShieldInteraction&)
        {
            this->_Explode(true);
            return false;
        }

        bool MissileEntity::Interact(WallInteraction&)
        {
            this->_Explode(false);
            return false;
        }

    }
}

