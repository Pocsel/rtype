#ifndef __REPULSEINTERACTION_HPP__
#define __REPULSEINTERACTION_HPP__

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class RepulseInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit RepulseInteraction(GameEntity* entity);
            ~RepulseInteraction();

            bool Interact(GameEntity& entity);

            Point const& GetPos() const;
            void SetPos(Point const& p);

        private:
            Point _pos;

        };

    }
}

#endif

