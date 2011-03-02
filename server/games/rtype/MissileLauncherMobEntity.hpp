#ifndef __MISSILELAUNCHERMOBENTITY_HPP__
#define __MISSILELAUNCHERMOBENTITY_HPP__

#include "MonsterEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MissileLauncherMobEntity : public MonsterEntity
        {
        public:
            explicit MissileLauncherMobEntity(Game& game, float y, bool move);
            ~MissileLauncherMobEntity();
        protected:
            void _Run(float time);
        private:
            enum
            {
                SPEED = 40
            };
            enum State
            {
                MOVING,
                FIRING
            };
            int _missiles;
            int _state;
            float _timeSave;
            bool _move;
        };

    }
}

#endif

