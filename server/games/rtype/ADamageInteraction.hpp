
#ifndef ADAMAGEINTERACTION_HPP_
# define ADAMAGEINTERACTION_HPP_

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ADamageInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit ADamageInteraction(size_t damage, GameEntity* entity);
            virtual ~ADamageInteraction(void);

            size_t GetValue(void) const;

        private:
            size_t _damage;
        };

    }
}

#endif // !ADAMAGEINTERACTION_HPP_
