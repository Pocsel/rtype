#include "MenuEntity.hpp"
#include "MainGame.hpp"
#include "EntityManager.hpp"

namespace Gmgp
{
    namespace Server
    {

        MenuEntity::MenuEntity(MainGame& game, String const& name, uint16_t playerId /* = 0 */) :
            _game(game), _name(name), _playerId(playerId)
        {
            this->_game.GetEntityManager().RegisterEntity(this);
        }

        MenuEntity::~MenuEntity()
        {
            this->_game.GetEntityManager().UnregisterEntity(this);
        }

        void MenuEntity::GenerateInteractions(float)
        {
        }

        void MenuEntity::Run(float)
        {
        }

        uint16_t MenuEntity::GetPlayerId() const
        {
            return this->_playerId;
        }

        void MenuEntity::SetPlayerId(uint16_t playerId)
        {
            this->_playerId = playerId;
        }

        void MenuEntity::SetName(String const& name)
        {
            this->_name = name;
        }

        String const& MenuEntity::GetName() const
        {
            return this->_name;
        }

    }
}

