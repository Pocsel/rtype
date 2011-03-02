
#ifndef MONSTERINTERACTION_HPP_
# define MONSTERINTERACTION_HPP_

#include "AInteraction.hpp"
#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MonsterInteraction : public AInteraction<GameEntity>
        {
        public:
            explicit MonsterInteraction(int life, GameEntity *entity = 0);

            ~MonsterInteraction(void);

            int Damage(int damage, uint16_t playerId);
            int GetLife(void) const;
            uint16_t GetLastHit(void) const;

            virtual bool Interact(GameEntity& entity);

        private:
            int _life;
            uint16_t _lastHit;
        };
    }
}

#endif // !MONSTERINTERACTION_HPP_
