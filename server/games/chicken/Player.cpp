#include "Player.hpp"
#include "ItemManager.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        Player::Player(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, Game& game) :
            BasicPlayer(id, nick, socketProxy, game), _game(game), _score(0)
        {
            this->_generator = new ChickenGeneratorEntity(game, id);
            this->_entity = new PlayerEntity(game, id);
        }

        Player::Player(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<Entity, Player>& game) :
            BasicPlayer(id, nick, socketProxy, game), _game(reinterpret_cast<Game&>(game)), _score(0)
        {
            this->_generator = new ChickenGeneratorEntity(this->_game, id);
            this->_entity = new PlayerEntity(this->_game, id);
        }

        Player::~Player()
        {
            delete this->_generator;
            delete this->_entity;
        }

        void Player::PutBigDamage(float posX, float posY)
        {
            this->_entity->PutBigDamage(posX, posY);
        }

        void Player::IncrementScore(uint32_t score)
        {
            this->_score += score;
        }

        uint32_t Player::GetScore(void) const
        {
            return this->_score;
        }

    }
}

