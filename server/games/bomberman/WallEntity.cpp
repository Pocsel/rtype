#include "WallEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "BonusEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        WallEntity::WallEntity(Game& game, int x, int y) :
            Entity(game, "Wall"), _noBonus(false)
        {
            this->_game.SetWall(Game::CaseToX(x), Game::CaseToY(y), true);
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::WALL));
            this->_sprite.SetPositionX(Game::CaseToX(x));
            this->_sprite.SetPositionY(Game::CaseToY(y));
            this->_game.GetItemManager().AddItem(&this->_sprite);
        }

        WallEntity::~WallEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
            this->_game.SetWall(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), false);
            Item ex;
            ex.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::WALL_DESTROY));
            ex.SetPositionX(this->_sprite.GetPositionX());
            ex.SetPositionY(this->_sprite.GetPositionY());
            ex.SetPositionZ(129);
            ex.SetLifeTimeCycles(1);
            this->_game.GetItemManager().SendItem(ex);
            if (!this->_noBonus && this->_game.R() > 0.75)
                new BonusEntity(this->_game, this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), this->_game.R() > 0.5 ? BonusEntity::POWER : BonusEntity::BOMB);
        }

        void WallEntity::Run(float)
        {
            this->_game.GetEntityManager().GetInteractionManager().Interact(*this, Point(this->_sprite.GetPositionX(),
                        this->_sprite.GetPositionY()));
        }

        bool WallEntity::Interact(BombInteraction& i)
        {
            if (i.GetPlayerId() == 0)
                this->_noBonus = true;
            delete this;
            return false;
        }

    }
}

