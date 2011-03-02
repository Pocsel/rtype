
#ifndef FORCEDOWNGRADEINTERACTION_HPP_
# define FORCEDOWNGRADEINTERACTION_HPP_


#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ForceDowngradeInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit ForceDowngradeInteraction(int playerId, GameEntity* entity);
            ~ForceDowngradeInteraction();

            bool Interact(GameEntity& entity);

            int GetPlayerId() const;

        private:
            int _playerId;
        };

    }
}

#endif // !FORCEDOWNGRADEINTERACTION_HPP_
