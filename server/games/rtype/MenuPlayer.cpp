#include "MenuPlayer.hpp"
#include "ItemManager.hpp"
#include "MainGame.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        MenuPlayer::MenuPlayer(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<MenuEntity, MenuPlayer>& game) :
            BasicPlayer(id, nick, socketProxy, game), _game(reinterpret_cast<MainGame&>(game))
        {
            this->_cursor.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::CURSOR));
            this->_cursor.SetCursor(true);
            this->_cursor.SetPositionZ(255);
            this->_cursor.SetPlayerId(id);
            this->_game.GetItemManager().AddItem(&this->_cursor);
            this->_mainMenu = new MainMenuEntity(this->_game, this->GetId());
        }

        MenuPlayer::~MenuPlayer()
        {
            this->_game.GetItemManager().RemoveItem(&this->_cursor);
            delete this->_mainMenu;
        }

    }
}

