#include "BonusEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        BonusEntity::BonusEntity(Game& game, float x, float y, int type) :
            Entity(game, "Bonus"), _bonus(new BonusInteraction(type))
        {
            if (type == POWER)
                this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BONUS_POWER));
            else
                this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BONUS_BOMB));
            this->_sprite.SetPositionX(x);
            this->_sprite.SetPositionY(y);
            this->_game.GetItemManager().AddItem(&this->_sprite);
        }

        BonusEntity::~BonusEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
        }

        void BonusEntity::GenerateInteractions(float)
        {
            if (!reinterpret_cast<BonusInteraction*>(this->_bonus.Get())->IsPickedUp())
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_bonus,
                        Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), Game::CASE_SIZE * 0.4f));
        }

        void BonusEntity::Run(float)
        {
            if (reinterpret_cast<BonusInteraction*>(this->_bonus.Get())->IsPickedUp())
                delete this;
            else
                this->_game.GetEntityManager().GetInteractionManager().Interact(*this, Point(this->_sprite.GetPositionX(),
                        this->_sprite.GetPositionY()));
        }

        bool BonusEntity::Interact(BombInteraction&)
        {
            delete this;
            return false;
        }

    }
}

