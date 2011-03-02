#include "GameEntity.hpp"
#include "Game.hpp"
#include "EntityManager.hpp"
#include "EnemyDamageInteraction.hpp"
#include "FriendlyDamageInteraction.hpp"
#include "MonsterInteraction.hpp"
#include "ShipInteraction.hpp"
#include "WallInteraction.hpp"
#include "ForceFireInteraction.hpp"
#include "ForceControlInteraction.hpp"
#include "ForceAttachInteraction.hpp"
#include "BonusInteraction.hpp"
#include "ShieldInteraction.hpp"
#include "RepulseInteraction.hpp"
#include "ForceUpgradeInteraction.hpp"
#include "ForceDowngradeInteraction.hpp"

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
        bool GameEntity::Interact(EnemyDamageInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(FriendlyDamageInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(MonsterInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(ShipInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(WallInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(ForceFireInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(ForceControlInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(ForceAttachInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(BonusInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(ShieldInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(TriggerInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(RepulseInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(ForceUpgradeInteraction&)
        {
            return true;
        }

        bool GameEntity::Interact(ForceDowngradeInteraction&)
        {
            return true;
        }

    }
}

