#include "GamePlayer.hpp"
#include "ItemManager.hpp"
#include "Game.hpp"
#include "PlayerEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        GamePlayer::GamePlayer(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<GameEntity, GamePlayer>& game) :
            BasicPlayer(id, nick, socketProxy, game), _game(reinterpret_cast<Game&>(game)), _score(0)
        {
            Log::I(this->GetNick() + " entered an R-Type game.");
            this->_player = new PlayerEntity(this->_game, id, nick);
        }

        GamePlayer::~GamePlayer()
        {
            Log::I(this->GetNick() + " left an R-Type game.");
            delete this->_player;
        }

        void GamePlayer::AddScore(size_t score)
        {
            this->_score += score;
        }

        size_t GamePlayer::GetScore() const
        {
            return this->_score;
        }

    }
}

