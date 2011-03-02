#include "RepulseInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        RepulseInteraction::RepulseInteraction(GameEntity* entity) :
            AInteraction<GameEntity>(entity)
        {
        }

        RepulseInteraction::~RepulseInteraction()
        {
        }

        Point const& RepulseInteraction::GetPos() const
        {
            return this->_pos;
        }

        void RepulseInteraction::SetPos(Point const& p)
        {
            this->_pos = p;
        }

        bool RepulseInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

    }
}

