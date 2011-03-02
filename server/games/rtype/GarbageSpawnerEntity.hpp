
#ifndef GARBAGESPAWNERENTITY_HPP_
# define GARBAGESPAWNERENTITY_HPP_

#include <queue>
#include <vector>

#include "GameEntity.hpp"
#include "Item.hpp"
#include "WallEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class GarbageSpawnerEntity : public WallEntity
        {
        private:
            struct GarbageInfo
            {
                GarbageInfo(int i, float w, float h) : id(i), width(w), height(h)
                {
                }
                int id;
                float width;
                float height;
            };
            enum
            {
                WIDTH = 64,
                HEIGHT = 32,
                CLOSE_HEIGHT = 24,
                MAX_FRAME = 3
            };
        public:
            explicit GarbageSpawnerEntity(Game& game, bool up);
            ~GarbageSpawnerEntity(void);

            virtual void GenerateInteractions(float time);
            virtual void Run(float time);

        private:
            void _IncreaseFrame(void);
            void _SpawnGarbage(void);
            void _Act(void);

            bool _up;
            int _curFrame;
            InteractionPtr _trigger;

            std::queue<void (GarbageSpawnerEntity::*)(void)> _actions;
            std::vector<GarbageInfo> _garbage;
            bool _triggered;
            bool _empty;
            float _nextActionTime;
        };

    }
}

#endif // !GARBAGESPAWNERENTITY_HPP_
