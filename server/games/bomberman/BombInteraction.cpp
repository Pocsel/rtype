
#include "BombInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        BombInteraction::BombInteraction(uint16_t playerId)
            : AInteraction<Entity>(0), _playerId(playerId)
        {
        }

        BombInteraction::~BombInteraction(void)
        {
        }

        bool BombInteraction::Interact(Entity& entity)
        {
            return entity.Interact(*this);
        }

        uint16_t BombInteraction::GetPlayerId(void) const
        {
            return this->_playerId;
        }

    }
}

