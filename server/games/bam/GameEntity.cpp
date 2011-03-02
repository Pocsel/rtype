#include "GameEntity.hpp"
#include "Game.hpp"
#include "EntityManager.hpp"

namespace Gmgp
{
    namespace Server
    {

        GameEntity::GameEntity(Game& game, String const& name, uint16_t playerId /* = 0 */) :
            _game(game), _name(name), _playerId(playerId)
        {
            this->_game.GetEntityManager().RegisterEntity(this);
        }

        GameEntity::~GameEntity()
        {
            this->_game.GetEntityManager().UnregisterEntity(this);
        }

        void GameEntity::GenerateInteractions(float)
        {
        }

        void GameEntity::Run(float)
        {
        }

        uint16_t GameEntity::GetPlayerId() const
        {
            return this->_playerId;
        }

        void GameEntity::SetPlayerId(uint16_t playerId)
        {
            this->_playerId = playerId;
        }

        void GameEntity::SetName(String const& name)
        {
            this->_name = name;
        }

        String const& GameEntity::GetName() const
        {
            return this->_name;
        }


        // Interactions

    }
}

