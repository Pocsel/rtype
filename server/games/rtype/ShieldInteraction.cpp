#include "ShieldInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        ShieldInteraction::ShieldInteraction(GameEntity* entity) :
            AInteraction<GameEntity>(entity)
        {
        }

        ShieldInteraction::~ShieldInteraction()
        {
        }

        bool ShieldInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

    }
}

