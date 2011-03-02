
#include "EnemyDamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        EnemyDamageInteraction::EnemyDamageInteraction(size_t damage,
                                                       GameEntity* entity /* = 0*/)
            : ADamageInteraction(damage, entity)
        {
        }

        bool EnemyDamageInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }
    }
}


