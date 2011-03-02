
#ifndef ENEMYDAMAGEINTERACTION_HPP_
# define ENEMYDAMAGEINTERACTION_HPP_

#include "ADamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class EnemyDamageInteraction : public ADamageInteraction
        {
        public:
            explicit EnemyDamageInteraction(size_t damage,
                                            GameEntity* entity = 0);

            virtual bool Interact(GameEntity& entity);
        };

    }
}

#endif // !ENEMYDAMAGEINTERACTION_HPP_
