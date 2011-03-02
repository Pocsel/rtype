#include "LuaMissileEntity.hpp"
#include "Game.hpp"
#include "BgTileEntity.hpp"
#include "Resources.hpp"
#include "EnemyDamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        LuaMissileEntity::LuaMissileEntity(Game& game, float posX, float posY, float speedX, float speedY, float accelX, float accelY) :
            GameEntity(game, "Lua missile"), _sprite(game.GetElapsedTime()), _dead(false), _damage(new EnemyDamageInteraction(10, this))
        {
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::ROTATING_MISSILE_FIXED));
            this->_sprite.SetLuaId(this->_game.GetResourceManager().GetResourceId(Resources::LUA_MISSILE));
            this->_sprite.SetPositionX(posX);
            this->_sprite.SetPositionY(posY);
            this->_sprite.SetSpeedX(speedX);
            this->_sprite.SetSpeedY(speedY);
            this->_sprite.SetAccelX(accelX);
            this->_sprite.SetAccelY(accelY);
            this->_game.GetItemManager().AddItem(&this->_sprite);
        }

        LuaMissileEntity::~LuaMissileEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
        }

        void LuaMissileEntity::_Explode(bool damage)
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

        void LuaMissileEntity::Run(float)
        {
            if (this->_sprite.GetPositionX() < -10 || this->_sprite.GetPositionY() > Game::HEIGHT + 10 ||
                this->_sprite.GetPositionX() > Game::WIDTH + 10 || this->_sprite.GetPositionY() < -10 ||
                this->_dead)
            {
                delete this;
                return;
            }
            this->_game.GetEntityManager().GetInteractionManager().Interact(*this,
                    Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 5));
        }

        bool LuaMissileEntity::Interact(ShipInteraction&)
        {
            this->_Explode(true);
            return false;
        }

        bool LuaMissileEntity::Interact(ShieldInteraction&)
        {
            this->_Explode(true);
            return false;
        }

        bool LuaMissileEntity::Interact(WallInteraction&)
        {
            this->_Explode(false);
            return false;
        }

    }
}

