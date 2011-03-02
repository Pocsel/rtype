
#ifndef LITTLEROBOTMOBENTITY_HPP_
# define LITTLEROBOTMOBENTITY_HPP_

#include "MonsterEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class LittleRobotMobEntity : public MonsterEntity
        {
        public:
            explicit LittleRobotMobEntity(Game& game, float y, bool reverse = false);
            ~LittleRobotMobEntity();

        protected:
            void _Run(float time);

        private:
            void _RandomizeVerticalSpeed(void);
            void _ShootBullet(void);

            float _nextBulletTime;
            float _nextMoveTime;
        };

    }
}

#endif // !LITTLEROBOTMOBENTITY_HPP_
