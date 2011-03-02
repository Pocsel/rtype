
#ifndef TRIGGERINTERACTION_HPP_
# define TRIGGERINTERACTION_HPP_

#include "AInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class GameEntity;

        class TriggerInteraction : public AInteraction<GameEntity>
        {
        public:
            TriggerInteraction(GameEntity* entity = 0);
            virtual ~TriggerInteraction(void);

            void Activate(void);
            bool IsActive(void) const;

            virtual bool Interact(GameEntity& entity);

        private:
            bool _active;
        };

    }
}

#endif // !TRIGGERINTERACTION_HPP_
