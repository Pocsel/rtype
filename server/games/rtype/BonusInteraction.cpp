#include "BonusInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        BonusInteraction::BonusInteraction(int type, GameEntity* entity) :
            AInteraction<GameEntity>(entity), _type(type), _isPickedUp(false)
        {
        }

        BonusInteraction::~BonusInteraction()
        {
        }

        void BonusInteraction::PickUp()
        {
            this->_isPickedUp = true;
        }

        bool BonusInteraction::IsPickedUp() const
        {
            return this->_isPickedUp;
        }

        int BonusInteraction::GetType() const
        {
            return this->_type;
        }

        bool BonusInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

    }
}

