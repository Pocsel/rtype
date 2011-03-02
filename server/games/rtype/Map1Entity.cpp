#include "Map1Entity.hpp"
#include "functor.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "WallEntity.hpp"
#include "WeakMobEntity.hpp"
#include "LittleRobotMobEntity.hpp"
#include "MissileEntity.hpp"
#include "MissileLauncherMobEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        Map1Entity::Map1Entity(Game& game) :
            MapEntity(game), _nbWeakMob(0), _nbLittleRobotMob(0)
        {
            float t = this->_game.GetElapsedTime();
            float step = 64.0f / Game::WALL_SPEED;
            this->_RegisterEvent(t + step * 1, b00st::bind(&Map1Entity::_WeakMob, *this));
            this->_RegisterEvent(t + step * 1.1f, b00st::bind(&Map1Entity::_WeakMob, *this));
            this->_RegisterEvent(t + step * 1.2f, b00st::bind(&Map1Entity::_WeakMob, *this));
            this->_RegisterEvent(t + step * 1.3f, b00st::bind(&Map1Entity::_WeakMob, *this));
            this->_RegisterEvent(t + step * 3, b00st::bind(&Map1Entity::_WeakMob, *this));
            this->_RegisterEvent(t + step * 3, b00st::bind(&Map1Entity::_WeakMob, *this));
            this->_RegisterEvent(t + step * 3, b00st::bind(&Map1Entity::_LowWallDown, *this));
            this->_RegisterEvent(t + step * 4, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 4, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 4, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 4, b00st::bind(&Map1Entity::_LowWallDown, *this));
            this->_RegisterEvent(t + step * 5, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 5, b00st::bind(&Map1Entity::_HighWallDown, *this));
            this->_RegisterEvent(t + step * 6, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 6, b00st::bind(&Map1Entity::_HighWallDown, *this));
            this->_RegisterEvent(t + step * 7, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 7, b00st::bind(&Map1Entity::_HighWallDown, *this));
            this->_RegisterEvent(t + step * 8, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 8, b00st::bind(&Map1Entity::_HighWallDown, *this));
            this->_RegisterEvent(t + step * 8, b00st::bind(&Map1Entity::_MissileLauncherMob, *this));
            this->_RegisterEvent(t + step * 9, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 9, b00st::bind(&Map1Entity::_HighWallDown, *this));
            this->_RegisterEvent(t + step * 9, b00st::bind(&Map1Entity::_MissileLauncherMob, *this));
            this->_RegisterEvent(t + step * 10, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 10, b00st::bind(&Map1Entity::_HighWallDown, *this));
            this->_RegisterEvent(t + step * 10, b00st::bind(&Map1Entity::_MissileLauncherMob, *this));
            this->_RegisterEvent(t + step * 11, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 11, b00st::bind(&Map1Entity::_HighWallDown, *this));
            this->_RegisterEvent(t + step * 11, b00st::bind(&Map1Entity::_MissileLauncherMob, *this));
            this->_RegisterEvent(t + step * 12, b00st::bind(&Map1Entity::_LittleRobotMob, *this));
            this->_RegisterEvent(t + step * 12, b00st::bind(&Map1Entity::_HighWallDown, *this));
            this->_RegisterEvent(t + step * 12, b00st::bind(&Map1Entity::_MissileLauncherMob, *this));

            this->_RegisterEvent(t + step * 0.5f, b00st::bind(&Map1Entity::_Test, *this));
            this->_RegisterEvent(t + step * 0.7f, b00st::bind(&Map1Entity::_Test, *this));
            this->_RegisterEvent(t + step * 1.5f, b00st::bind(&Map1Entity::_Test, *this));
            this->_RegisterEvent(t + step * 1.7f, b00st::bind(&Map1Entity::_Test, *this));
            this->_RegisterEvent(t + step * 2.5f, b00st::bind(&Map1Entity::_Test, *this));
            this->_RegisterEvent(t + step * 2.7f, b00st::bind(&Map1Entity::_Test, *this));
        }

        Map1Entity::~Map1Entity()
        {
        }

        void Map1Entity::_Test()
        {
        }

        void Map1Entity::_MissileLauncherMob()
        {
            new MissileLauncherMobEntity(this->_game, 180, true);
        }

        void Map1Entity::_WeakMob()
        {
            new WeakMobEntity(this->_game, 60 + (this->_nbWeakMob % 4) * 20.0f);
            ++this->_nbWeakMob;
        }

        void Map1Entity::_LittleRobotMob()
        {
            new LittleRobotMobEntity(this->_game, Game::HEIGHT / 2 - 10 + (this->_nbLittleRobotMob % 4) * 5.0f);
            ++this->_nbLittleRobotMob;
        }

        void Map1Entity::_LowWallUp()
        {
            int res = Resources::WALL1_UP_64x16_1;
            float r = this->_game.R();
            if (r > 0.66)
                res = Resources::WALL1_UP_64x16_2;
            else if (r > 0.33)
                res = Resources::WALL1_UP_64x16_3;
            new WallEntity(this->_game, res, true, 64, 16);
        }

        void Map1Entity::_LowWallDown()
        {
            int res = Resources::WALL1_DOWN_64x16_1;
            float r = this->_game.R();
            if (r > 0.66)
                res = Resources::WALL1_DOWN_64x16_2;
            else if (r > 0.33)
                res = Resources::WALL1_DOWN_64x16_3;
            new WallEntity(this->_game, res, false, 64, 16);
        }

        void Map1Entity::_HighWallUp()
        {
            new WallEntity(this->_game, Resources::WALL1_UP_64x48_1, true, 64, 48);
        }

        void Map1Entity::_HighWallDown()
        {
            new WallEntity(this->_game, Resources::WALL1_DOWN_64x48_1, false, 64, 48);
        }

    }
}

