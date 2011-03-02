#include "ForceAttachInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        ForceAttachInteraction::ForceAttachInteraction(uint16_t playerId, bool isFront, GameEntity* entity) :
            AInteraction<GameEntity>(entity), _playerId(playerId), _isFront(isFront)
        {
        }

        ForceAttachInteraction::~ForceAttachInteraction()
        {
        }

        bool ForceAttachInteraction::IsFront() const
        {
            return this->_isFront;
        }

        uint16_t ForceAttachInteraction::GetPlayerId() const
        {
            return this->_playerId;
        }

        bool ForceAttachInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

    }
}

