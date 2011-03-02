#ifndef __MONSTERGENERATORENTITY_HPP__
#define __MONSTERGENERATORENTITY_HPP__

#include <vector>

#include "MonsterEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MonsterGeneratorEntity : public GameEntity
        {
        public:
            enum Type
            {
                WEAK,
                LITTLE_ROBOT,
                LITTLE_ROBOT_REVERSE,
            };

        public:
            explicit MonsterGeneratorEntity(Game& game, float delay, float number, Type type);
            ~MonsterGeneratorEntity();
            void Run(float time);

            void SpawnNow(void);

        private:
            void _SpawnWeak(void);
            void _SpawnLittleRobot(void);
            void _SpawnLittleRobotReverse(void);

        public:
            float delay;
            float number;
            Type type;

        private:
            float _nextSpawn;

            std::vector<void (MonsterGeneratorEntity::*)(void)> _spawns;
        };

    }
}

#endif

