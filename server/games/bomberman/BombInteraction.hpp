
#ifndef BOMBINTERACTION_HPP_
# define BOMBINTERACTION_HPP_

#include "AInteraction.hpp"
#include "Entity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class BombInteraction : public AInteraction<Entity>
        {
        public:
            explicit BombInteraction(uint16_t playerId);
            virtual ~BombInteraction(void);

            virtual bool Interact(Entity& entity);

            uint16_t GetPlayerId(void) const;

        private:
            uint16_t _playerId;
        };
    }
}

#endif // !BOMBINTERACTION_HPP_
