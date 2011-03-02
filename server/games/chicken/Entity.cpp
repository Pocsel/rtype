#include "Entity.hpp"
#include "EntityManager.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        Entity::Entity(Game& game, String const& name, uint16_t playerId /* = 0 */) :
            _game(game), _name(name), _playerId(playerId)
        {
            this->_game.GetEntityManager().RegisterEntity(this);
        }

        Entity::~Entity()
        {
            this->_game.GetEntityManager().UnregisterEntity(this);
        }

        void Entity::GenerateInteractions(float)
        {
        }

        void Entity::Run(float)
        {
        }

        uint16_t Entity::GetPlayerId() const
        {
            return this->_playerId;
        }

        void Entity::SetPlayerId(uint16_t playerId)
        {
            this->_playerId = playerId;
        }

        void Entity::SetName(String const& name)
        {
            this->_name = name;
        }

        String const& Entity::GetName() const
        {
            return this->_name;
        }

        bool Entity::Interact(DamageInteraction&)
        {
            return false;
        }

    }
}

