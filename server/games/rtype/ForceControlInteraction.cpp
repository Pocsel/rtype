#include "ForceControlInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        ForceControlInteraction::ForceControlInteraction(uint16_t playerId, GameEntity* entity) :
            AInteraction<GameEntity>(entity), _playerId(playerId)
        {
        }

        ForceControlInteraction::~ForceControlInteraction()
        {
        }

        bool ForceControlInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

        uint16_t ForceControlInteraction::GetPlayerId() const
        {
            return this->_playerId;
        }

        void ForceControlInteraction::SetPos(Point const& p)
        {
            this->_pos = p;
        }

        Point const& ForceControlInteraction::GetPos() const
        {
            return this->_pos;
        }

    }
}

