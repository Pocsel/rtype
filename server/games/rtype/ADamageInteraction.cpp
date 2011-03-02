
#include "ADamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        ADamageInteraction::ADamageInteraction(size_t damage, GameEntity* entity)
            : AInteraction<GameEntity>(entity), _damage(damage)
        {
        }

        ADamageInteraction::~ADamageInteraction(void)
        {
        }

        size_t ADamageInteraction::GetValue(void) const
        {
            return this->_damage;
        }

    }
}

