#ifndef __BONUSINTERACTION_HPP__
#define __BONUSINTERACTION_HPP__

#include "AInteraction.hpp"
#include "Entity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class BonusInteraction : public AInteraction<Entity>
        {
        public:
            explicit BonusInteraction(int type);
            virtual ~BonusInteraction(void);

            virtual bool Interact(Entity& entity);

            int GetType() const;
            bool IsPickedUp() const;
            void PickedUp();

        private:
            int _type;
            bool _pickedUp;
        };
    }
}

#endif

