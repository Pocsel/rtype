
#include "ForceDowngradeInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        ForceDowngradeInteraction::ForceDowngradeInteraction(int playerId, GameEntity* entity)
            : AInteraction<GameEntity>(entity), _playerId(playerId)
        {
        }

        ForceDowngradeInteraction::~ForceDowngradeInteraction()
        {
        }

        bool ForceDowngradeInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

        int ForceDowngradeInteraction::GetPlayerId() const
        {
            return this->_playerId;
        }

    }
}

