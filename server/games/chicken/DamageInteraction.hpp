
#ifndef DAMAGEINTERACTION_HPP_
# define DAMAGEINTERACTION_HPP_

#include "AInteraction.hpp"
#include "Circle.hpp"
#include "Rect.hpp"
#include "Point.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Entity;

        class DamageInteraction : public AInteraction<Entity>
        {
        public:
            explicit DamageInteraction(size_t damage,  uint16_t playerId, Entity* entity = 0);
            ~DamageInteraction(void);

            virtual bool Interact(Entity& entity);

            size_t GetValue() const;
            uint16_t GetPlayerId(void) const;

        private:
            size_t _damage;
            uint16_t _playerId;
        };

    }
}

#endif // !DAMAGEINTERACTION_HPP_
