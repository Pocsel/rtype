#ifndef __MAP1ENTITY_HPP__
#define __MAP1ENTITY_HPP__

#include "MapEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Map1Entity : public MapEntity
        {
        public:
            Map1Entity(Game& game);
            virtual ~Map1Entity();

        private:
            size_t _nbWeakMob;
            size_t _nbLittleRobotMob;
            void _WeakMob();
            void _LittleRobotMob();
            void _MissileLauncherMob();
            void _LowWallUp();
            void _LowWallDown();
            void _HighWallUp();
            void _HighWallDown();
            void _Test();
        };

    }
}

#endif

