
#include "WallGeneratorEntity.hpp"
#include "Game.hpp"
#include "WallEntity.hpp"
#include "Resources.hpp"
#include "GarbageSpawnerEntity.hpp"
#include "MissileLauncherMobEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        WallGeneratorEntity::WallGeneratorEntity(Game& game, int wallSet, size_t specialAmount) :
            GameEntity(game, "Wall Generator"),
            _nextUpSpawn(0),
            _nextDownSpawn(0),
            _special(true)
        {
            if (wallSet > 1)
                wallSet = 1;
            switch (wallSet)
            {
                case 0:
                    this->_upWalls.push_back(WallInfo(Resources::WALL1_UP_64x16_1, 64, 16, &WallGeneratorEntity::_Nothing));
                    this->_upWalls.push_back(WallInfo(Resources::WALL1_UP_64x16_2, 64, 16, &WallGeneratorEntity::_Nothing));
                    this->_upWalls.push_back(WallInfo(Resources::WALL1_UP_64x16_3, 64, 16, &WallGeneratorEntity::_Nothing));
                    this->_upWalls.push_back(WallInfo(Resources::WALL1_UP_64x48_1, 64, 48, &WallGeneratorEntity::_Nothing));

                    this->_downWalls.push_back(WallInfo(Resources::WALL1_DOWN_64x16_1, 64, 16, &WallGeneratorEntity::_Nothing));
                    this->_downWalls.push_back(WallInfo(Resources::WALL1_DOWN_64x16_2, 64, 16, &WallGeneratorEntity::_Nothing));
                    this->_downWalls.push_back(WallInfo(Resources::WALL1_DOWN_64x16_3, 64, 16, &WallGeneratorEntity::_Nothing));
                    this->_downWalls.push_back(WallInfo(Resources::WALL1_DOWN_64x48_1, 64, 48, &WallGeneratorEntity::_Nothing));

                    for (size_t i = 0 ; i < specialAmount ; ++i)
                    {
                        this->_downWalls.push_back(WallInfo(Resources::WALL1_DOWN_64x48_1, 64, 48, &WallGeneratorEntity::_MissileLauncherHigh));
                        this->_downWalls.push_back(WallInfo(Resources::WALL1_DOWN_64x16_3, 64, 16, &WallGeneratorEntity::_MissileLauncherLow));
                    }
                    break;

                case 1:
                    this->_upWalls.push_back(WallInfo(Resources::WALL2_UP_64x16_1, 64, 16, &WallGeneratorEntity::_Nothing));
                    this->_upWalls.push_back(WallInfo(Resources::WALL2_UP_64x48_1, 64, 48, &WallGeneratorEntity::_Nothing));
                    this->_upWalls.push_back(WallInfo(Resources::WALL2_UP_128x16_1, 128, 16, &WallGeneratorEntity::_Nothing));
                    this->_upWalls.push_back(WallInfo(Resources::WALL2_UP_128x48_1, 128, 48, &WallGeneratorEntity::_Nothing));

                    this->_downWalls.push_back(WallInfo(Resources::WALL2_DOWN_64x16_1, 64, 16, &WallGeneratorEntity::_Nothing));
                    this->_downWalls.push_back(WallInfo(Resources::WALL2_DOWN_64x48_1, 64, 48, &WallGeneratorEntity::_Nothing));
                    this->_downWalls.push_back(WallInfo(Resources::WALL2_DOWN_128x16_1, 128, 16, &WallGeneratorEntity::_Nothing));
                    this->_downWalls.push_back(WallInfo(Resources::WALL2_DOWN_128x48_1, 128, 48, &WallGeneratorEntity::_Nothing));

                    for (size_t i = 0 ; i < specialAmount ; ++i)
                    {
                        this->_upWalls.push_back(WallInfo(Resources::WALL2_UP_64x16_1, 64, 16, &WallGeneratorEntity::_GarbageSpawnerUp));
                        this->_downWalls.push_back(WallInfo(Resources::WALL2_DOWN_64x16_1, 64, 16, &WallGeneratorEntity::_GarbageSpawnerDown));
                    }
                    break;
            }
        }

        WallGeneratorEntity::~WallGeneratorEntity()
        {
        }

        void WallGeneratorEntity::Run(float time)
        {
            if (time >= this->_nextUpSpawn)
            {
                int r = this->_game.R() * this->_upWalls.size();
                WallInfo const& info = this->_upWalls[r];
                new WallEntity(this->_game, info.resourceLocalId, true, info.width, info.height);
                if (this->_special)
                    (this->*info.specialAbility)();

                int x = this->_game.R() * 1.2f;
                this->_nextUpSpawn = time + (1 + x) * (info.width * 0.05f);
            }

            if (time >= this->_nextDownSpawn)
            {
                int r = this->_game.R() * this->_downWalls.size();
                WallInfo const& info = this->_downWalls[r];
                new WallEntity(this->_game, info.resourceLocalId, false, info.width, info.height);
                if (this->_special)
                    (this->*info.specialAbility)();

                int x = this->_game.R() * 1.2f;
                this->_nextDownSpawn = time + (1 + x) * (info.width * 0.05f);
            }
        }

        void WallGeneratorEntity::StopSpecial(void)
        {
            this->_special = false;
        }

        void WallGeneratorEntity::_Nothing(void)
        {
        }

        void WallGeneratorEntity::_MissileLauncherHigh(void)
        {
            new MissileLauncherMobEntity(this->_game, 180, false);
        }

        void WallGeneratorEntity::_MissileLauncherLow(void)
        {
            new MissileLauncherMobEntity(this->_game, 212, false);
        }

        void WallGeneratorEntity::_GarbageSpawnerUp(void)
        {
            new GarbageSpawnerEntity(this->_game, true);
        }

        void WallGeneratorEntity::_GarbageSpawnerDown(void)
        {
            new GarbageSpawnerEntity(this->_game, false);
        }


    }
}


