
#include "ForceUpgradeInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        ForceUpgradeInteraction::ForceUpgradeInteraction(int type, int playerId, GameEntity* entity)
            : AInteraction<GameEntity>(entity), _type(type), _playerId(playerId)
        {
        }

        ForceUpgradeInteraction::~ForceUpgradeInteraction()
        {
        }

        bool ForceUpgradeInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

        int ForceUpgradeInteraction::GetType() const
        {
            return this->_type;
        }

        int ForceUpgradeInteraction::GetPlayerId() const
        {
            return this->_playerId;
        }

    }
}
