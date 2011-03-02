#ifndef __FILEMAPENTITY_HPP__
#define __FILEMAPENTITY_HPP__

#include <map>
#include "GameEntity.hpp"
#include "Item.hpp"
#include "MapEntity.hpp"
#include "TextEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class FileMapEntity : public MapEntity
        {
            public:
                FileMapEntity(Game& game, String const& filename);
                virtual ~FileMapEntity();
            private:
                std::map<char, void (FileMapEntity::*)(void)> _objects;
                size_t _nbWeakMob;
                size_t _nbLittleRobotMob;
                size_t _nbBonus;
                TextEntity<GameEntity, Game>* _nameText;
                void _LowWallDown();
                void _LowWallUp();
                void _HighWallDown();
                void _HighWallUp();
                void _LowGreenWallDown();
                void _LowGreenWallUp();
                void _HighGreenWallDown();
                void _HighGreenWallUp();
                void _GarbageSpawnerDown();
                void _GarbageSpawnerUp();
                void _LowMovingMissileLauncherMob();
                void _HighMovingMissileLauncherMob();
                void _LowFixedMissileLauncherMob();
                void _HighFixedMissileLauncherMob();
                void _WeakMob();
                void _FrontLittleRobotMob();
                void _BackLittleRobotMob();
                void _ForceBonus();
                void _SpeedBonus();
                void _MissileBonus();
                void _FlameBonus();
                void _LaserBonus();
                void _DnaBonus();
                void _Boss1();
        };

    }
}

#endif

