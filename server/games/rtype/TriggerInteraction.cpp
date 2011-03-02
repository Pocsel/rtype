
#include "TriggerInteraction.hpp"
#include "GameEntity.hpp"


namespace Gmgp
{
    namespace Server
    {

            TriggerInteraction::TriggerInteraction(GameEntity* entity)
                : AInteraction<GameEntity>(entity), _active(false)
            {
            }

            TriggerInteraction::~TriggerInteraction(void)
            {
            }

            void TriggerInteraction::Activate(void)
            {
                this->_active = true;
            }

            bool TriggerInteraction::IsActive(void) const
            {
                return this->_active;
            }

            bool TriggerInteraction::Interact(GameEntity& entity)
            {
                return entity.Interact(*this);
            }

    }
}


