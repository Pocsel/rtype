
#ifndef FORCEUPGRADEINTERACTION_HPP_
# define FORCEUPGRADEINTERACTION_HPP_

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ForceUpgradeInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit ForceUpgradeInteraction(int type, int playerId, GameEntity* entity);
            ~ForceUpgradeInteraction();

            bool Interact(GameEntity& entity);

            int GetType() const;
            int GetPlayerId() const;

        private:
            int _type;
            int _playerId;
        };

    }
}

#endif // !FORCEUPGRADEINTERACTION_HPP_
