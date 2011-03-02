
#include "BgTileEntity.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        BgTileEntity::BgTileEntity(Game& game, uint16_t resourceId, float x, float y, float width, float z, float speed)
            : GameEntity(game, "BgTile"), _sprite(game.GetElapsedTime()), _width(width), _speed(speed)
        {
            this->_sprite.SetResourceId(resourceId);
            this->_sprite.SetPositionX(x);
            this->_sprite.SetPositionY(y);
            this->_sprite.SetPositionZ(z);
            this->_sprite.SetSpeedX(this->_speed);
            this->_game.GetItemManager().AddItem(&this->_sprite);
            this->_game.RegisterBgTile(this);
        }

        BgTileEntity::~BgTileEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
        }

        void BgTileEntity::Run(float)
        {
            if (this->_sprite.GetPositionX() < -(this->_width / 2))
            {
                this->_game.UnregisterBgTile(this);
                delete this;
                return;
            }
        }

        void BgTileEntity::Stop(void)
        {
            this->_sprite.SetSpeedX(0);
        }

        void BgTileEntity::Go(void)
        {
            this->_sprite.SetSpeedX(this->_speed);
        }

    }
}

