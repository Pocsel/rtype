
#include "DamageInteraction.hpp"
#include "Entity.hpp"

namespace Gmgp
{
    namespace Server
    {

        DamageInteraction::DamageInteraction(size_t damage, uint16_t playerId, Entity* entity /* = 0 */)
            : AInteraction<Entity>(entity), _damage(damage), _playerId(playerId)
        {
        }

        DamageInteraction::~DamageInteraction(void)
        {
        }

        size_t DamageInteraction::GetValue() const
        {
            return this->_damage;
        }

        uint16_t DamageInteraction::GetPlayerId(void) const
        {
            return this->_playerId;
        }

        bool DamageInteraction::Interact(Entity& entity)
        {
            return entity.Interact(*this);
        }

    }
}

