#include "Player.hpp"
#include "ItemManager.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        Player::Player(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<Entity, Player>& game) :
            BasicPlayer(id, nick, socketProxy, game), _game(reinterpret_cast<Game&>(game))
        {
            this->_menu = new MenuEntity(this->_game, id, nick);
        }

        Player::~Player()
        {
            delete this->_menu;
        }

    }
}

