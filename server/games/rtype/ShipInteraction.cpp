
#include "ShipInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        ShipInteraction::ShipInteraction(uint16_t playerId, GameEntity *entity /* = 0 */)
            : AInteraction<GameEntity>(entity), _playerId(playerId)
        {
        }

        ShipInteraction::~ShipInteraction(void)
        {
        }

        uint16_t ShipInteraction::GetPlayerId(void) const
        {
            return this->_playerId;
        }

        bool ShipInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

    }
}

