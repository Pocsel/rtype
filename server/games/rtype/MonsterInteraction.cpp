
#include "MonsterInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        MonsterInteraction::MonsterInteraction(int life, GameEntity *entity /* = 0 */)
            : AInteraction<GameEntity>(entity), _life(life), _lastHit(0)
        {
        }

        MonsterInteraction::~MonsterInteraction(void)
        {
        }

        int MonsterInteraction::Damage(int damage, uint16_t playerId)
        {
            this->_lastHit = playerId;
            this->_life -= damage;
            if (this->_life <= 0)
            {
                return damage + this->_life;
                this->_life = 0;
            }
            return damage;
        }

        int MonsterInteraction::GetLife(void) const
        {
            return this->_life;
        }

        uint16_t MonsterInteraction::GetLastHit(void) const
        {
            return this->_lastHit;
        }

        bool MonsterInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

    }
}

