#ifndef __SHIELDINTERACTION_HPP__
#define __SHIELDINTERACTION_HPP__

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ShieldInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit ShieldInteraction(GameEntity* entity);
            ~ShieldInteraction();

            bool Interact(GameEntity& entity);

        private:

        };

    }
}

#endif

