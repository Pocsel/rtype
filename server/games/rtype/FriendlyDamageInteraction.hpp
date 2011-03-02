
#ifndef FRIENDLYDAMAGEINTERACTION_HPP_
# define FRIENDLYDAMAGEINTERACTION_HPP_

#include "ADamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class FriendlyDamageInteraction : public ADamageInteraction
        {
        public:
            explicit FriendlyDamageInteraction(size_t damage,
                                               uint16_t playerId,
                                               GameEntity* entity = 0);

            virtual bool Interact(GameEntity& entity);

            uint16_t GetPlayerId(void) const;
            void SetPlayerId(uint16_t playerId);

        private:
            uint16_t _playerId;
        };

    }
}

#endif // !FRIENDLYDAMAGEINTERACTION_HPP_
