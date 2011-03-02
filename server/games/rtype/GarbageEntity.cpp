
#include "GarbageEntity.hpp"
#include "Game.hpp"
#include "WallInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        GarbageEntity::GarbageEntity(Game& game, int resourceLocalId, bool up, float width, float height, float posX)
            : GameEntity(game, "Garbage"), _sprite(game.GetElapsedTime()), _interaction(new WallInteraction()),
            _width(width), _height(height)
        {
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(resourceLocalId));
            this->_sprite.SetPositionX(posX);
            this->_sprite.SetPositionY(up ? 32.0f : Game::HEIGHT - 32.0f);
            this->_sprite.SetPositionZ(169);
            this->_sprite.SetSpeedX(-Game::WALL_SPEED + 40 - this->_game.R() * 80);
            this->_sprite.SetSpeedY(up ? this->_game.R() * 40 : -100 - this->_game.R() * 200);
            this->_sprite.SetAccelY(200);
            this->_game.GetItemManager().AddItem(&this->_sprite);

            reinterpret_cast<WallInteraction*>(this->_interaction.Get())->SetSize(width, height);
        }

        GarbageEntity::~GarbageEntity(void)
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
        }

        void GarbageEntity::GenerateInteractions(float)
        {
            reinterpret_cast<WallInteraction*>(this->_interaction.Get())->SetPosition(this->_sprite.GetPositionX(), this->_sprite.GetPositionY());
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_interaction,
                                                                                  Rect(this->_sprite.GetPositionX() - this->_width * 0.5f,
                                                                                       this->_sprite.GetPositionY() - this->_height * 0.5f,
                                                                                       this->_width, this->_height));
        }

        void GarbageEntity::Run(float)
        {
            if (this->_sprite.GetPositionY() > Game::HEIGHT)
                delete this;
        }

    }
}

