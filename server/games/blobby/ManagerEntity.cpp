
#include "ManagerEntity.hpp"
#include "Resources.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        ManagerEntity::ManagerEntity(Game& game)
            : Common2ManagerEntity<Entity, Game, PlayerEntity>(game, 2),
            _ball(game)
        {
            this->_bar.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BAR));
            this->_bar.SetPositionX(Game::FULLWIDTH / 2);
            this->_bar.SetPositionY(Game::FULLHEIGHT - BAR_HEIGHT / 2);
            this->_game.GetItemManager().AddItem(&this->_bar);
        }

        ManagerEntity::~ManagerEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_bar);
        }

        int ManagerEntity::_GetIconId() const
        {
            return Resources::P1_ICON;
        }

        int ManagerEntity::_GetBgId() const
        {
            return Resources::BACKGROUND;
        }

        void ManagerEntity::_SpawnMap()
        {
        }

        void ManagerEntity::_DestroyMap()
        {
        }

    }
}

