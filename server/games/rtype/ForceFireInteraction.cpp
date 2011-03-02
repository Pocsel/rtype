#include "ForceFireInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        ForceFireInteraction::ForceFireInteraction(uint16_t playerId, GameEntity* entity) :
            AInteraction<GameEntity>(entity), _playerId(playerId)
        {
        }

        ForceFireInteraction::~ForceFireInteraction()
        {
        }

        bool ForceFireInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

        uint16_t ForceFireInteraction::GetPlayerId() const
        {
            return this->_playerId;
        }

    }
}

