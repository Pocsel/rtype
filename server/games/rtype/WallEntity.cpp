
#include "WallEntity.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        WallEntity::WallEntity(Game& game, int resourceLocalId, bool up, float width, float height)
            : GameEntity(game, "Wall"),
            _sprite(game.GetElapsedTime()),
            _interaction(new WallInteraction()),
            _width(width),
            _height(height)
        {
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(resourceLocalId));
            this->_sprite.SetPositionX(Game::WIDTH + width * 0.5f);
            this->_sprite.SetPositionY(up ? (0 + height * 0.5f) : (Game::HEIGHT - height * 0.5f));
            this->_sprite.SetSpeedX(-Game::WALL_SPEED);
            this->_sprite.SetPositionZ(170);
            this->_game.GetItemManager().AddItem(&this->_sprite);

            reinterpret_cast<WallInteraction*>(this->_interaction.Get())->SetSize(width, height);

            this->_game.RegisterWall(this);
        }

        WallEntity::~WallEntity(void)
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
            this->_game.UnregisterWall(this);
        }

        void WallEntity::GenerateInteractions(float)
        {
            reinterpret_cast<WallInteraction*>(this->_interaction.Get())->SetPosition(this->_sprite.GetPositionX(), this->_sprite.GetPositionY());
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_interaction,
                                                                                  Rect(this->_sprite.GetPositionX() - this->_width * 0.5f,
                                                                                       this->_sprite.GetPositionY() - this->_height * 0.5f,
                                                                                       this->_width, this->_height));
        }

        void WallEntity::Run(float)
        {
            if (this->_sprite.GetPositionX() + this->_width * 0.5 < 0)
                delete this;
        }

        void WallEntity::Stop(void)
        {
            this->_sprite.SetSpeedX(0);
        }

        void WallEntity::Go(void)
        {
            this->_sprite.SetSpeedX(-Game::WALL_SPEED);
        }

    }
}
