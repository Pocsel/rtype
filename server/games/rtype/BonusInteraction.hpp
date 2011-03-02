#ifndef __BONUSINTERACTION_HPP__
#define __BONUSINTERACTION_HPP__

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class BonusInteraction : public AInteraction<GameEntity>
        {
        public:
            enum Type
            {
                FORCE = 0,
                SPEED = 1,
                FORCE_DNA_STYLE = 2,
                FORCE_BOING_LASER = 3,
                FORCE_FLAME_THROWER = 4,
                FORCE_EXPLOSIVE = 5,
            };

            explicit BonusInteraction(int type, GameEntity* entity = 0);
            ~BonusInteraction();

            bool Interact(GameEntity& entity);

            void PickUp();
            bool IsPickedUp() const;
            int GetType() const;

        private:
            int _type;
            bool _isPickedUp;

        };

    }
}

#endif

