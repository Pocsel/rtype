
#ifndef WALLGENERATORENTITY_HPP_
# define WALLGENERATORENTITY_HPP_

#include <vector>

#include "GameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class WallGeneratorEntity : public GameEntity
        {
        private:
            struct WallInfo
            {
                WallInfo(int r, float w, float h, void (WallGeneratorEntity::*s)(void))
                    : resourceLocalId(r), width(w), height(h), specialAbility(s)
                {
                }
                int resourceLocalId;
                float width;
                float height;
                void (WallGeneratorEntity::*specialAbility)(void);
                //time = width * 0.05
            };

        public:
            explicit WallGeneratorEntity(Game& game, int wallSet, size_t specialAmount = 1);
            ~WallGeneratorEntity();
            void Run(float time);
            void StopSpecial(void);

        private:
            void _Nothing(void);
            void _GarbageSpawnerUp(void);
            void _GarbageSpawnerDown(void);
            void _MissileLauncherLow(void);
            void _MissileLauncherHigh(void);

            float _nextUpSpawn;
            float _nextDownSpawn;
            std::vector<WallInfo> _upWalls;
            std::vector<WallInfo> _downWalls;
            bool _special;
        };

    }
}

#endif // !WALLGENERATORENTITY_HPP_
