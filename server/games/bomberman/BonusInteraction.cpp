#include "BonusInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        BonusInteraction::BonusInteraction(int type)
            : AInteraction<Entity>(0), _type(type), _pickedUp(false)
        {
        }

        BonusInteraction::~BonusInteraction(void)
        {
        }

        void BonusInteraction::PickedUp()
        {
            this->_pickedUp = true;
        }

        bool BonusInteraction::IsPickedUp() const
        {
            return this->_pickedUp;
        }

        bool BonusInteraction::Interact(Entity& entity)
        {
            return entity.Interact(*this);
        }

        int BonusInteraction::GetType() const
        {
            return this->_type;
        }

    }
}

