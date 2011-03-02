
#include "BonusEntity.hpp"
#include "Game.hpp"
#include "BonusInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        BonusEntity::BonusEntity(Game& game, int type, int spriteId, float x, float y)
            : GameEntity(game, "Bonus"),
            _sprite(game.GetElapsedTime()),
            _interaction(new BonusInteraction(type))
        {
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(spriteId));
            this->_sprite.SetPositionX(x);
            this->_sprite.SetPositionY(y);
            this->_sprite.SetPositionZ(165);
            this->_sprite.SetSpeedX(-Game::WALL_SPEED);
            this->_game.GetItemManager().AddItem(&this->_sprite);
        }

        BonusEntity::~BonusEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
        }

        void BonusEntity::GenerateInteractions(float)
        {
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_interaction, Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), RADIUS));
        }

        void BonusEntity::Run(float)
        {
            if (reinterpret_cast<BonusInteraction*>(this->_interaction.Get())->IsPickedUp() ||
                this->_sprite.GetPositionX() < -RADIUS)
            {
                delete this;
            }
        }
    }
}
