
#include "FriendlyDamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        FriendlyDamageInteraction::FriendlyDamageInteraction(size_t damage,
                                                             uint16_t playerId,
                                                             GameEntity* entity /* = 0*/)
            : ADamageInteraction(damage, entity), _playerId(playerId)
        {
        }

        uint16_t FriendlyDamageInteraction::GetPlayerId(void) const
        {
            return this->_playerId;
        }

        void FriendlyDamageInteraction::SetPlayerId(uint16_t playerId)
        {
            this->_playerId = playerId;
        }

        bool FriendlyDamageInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

    }
}


