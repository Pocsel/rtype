
#ifndef BONUSCARRIERMOBENTITY_HPP_
# define BONUSCARRIERMOBENTITY_HPP_

#include "MonsterEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class BonusCarrierMobEntity : public MonsterEntity
        {
        public:
            explicit BonusCarrierMobEntity(Game& game, float y, int bonusType, int bonusLocalId);
            ~BonusCarrierMobEntity();

        protected:
            void _Run(float time);

        private:
            void _RandomizeVerticalSpeed(void);
            float _nextMoveTime;
            int _bonusType;
            int _bonusLocalId;
        };

    }
}

#endif // !BONUSCARRIERMOBENTITY_HPP_
