#include "Player.hpp"
#include "ItemManager.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        Player::Player(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<Entity, Player>& game) :
            BasicPlayer(id, nick, socketProxy, game), _game(reinterpret_cast<Game&>(game)), _score(0)
        {
            Log::I(this->GetNick() + " entered a bomberman game.");
            this->_player = new PlayerEntity(this->_game, id, nick);
        }

        Player::~Player()
        {
            Log::I(this->GetNick() + " left a bomberman game.");
            delete this->_player;
        }

        int Player::GetScore() const
        {
            return this->_score;
        }

        void Player::AddToScore(int val)
        {
            this->_score += val;
        }

    }
}

