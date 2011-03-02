#include <fstream>
#include "FileMapEntity.hpp"
#include "functor.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "WallEntity.hpp"
#include "WeakMobEntity.hpp"
#include "LittleRobotMobEntity.hpp"
#include "MissileEntity.hpp"
#include "MissileLauncherMobEntity.hpp"
#include "GarbageSpawnerEntity.hpp"
#include "BonusCarrierMobEntity.hpp"
#include "BonusInteraction.hpp"
#include "Boss1Entity.hpp"
#include "LuaMissileEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        FileMapEntity::FileMapEntity(Game& game, String const& filepath) :
            MapEntity(game), _nbWeakMob(0), _nbLittleRobotMob(0), _nbBonus(0), _nameText(0)
        {
            this->_objects['['] = &FileMapEntity::_LowWallDown;
            this->_objects[']'] = &FileMapEntity::_LowWallUp;
            this->_objects['<'] = &FileMapEntity::_HighWallDown;
            this->_objects['>'] = &FileMapEntity::_HighWallUp;
            this->_objects['/'] = &FileMapEntity::_LowGreenWallDown;
            this->_objects['\\'] = &FileMapEntity::_LowGreenWallUp;
            this->_objects['('] = &FileMapEntity::_HighGreenWallDown;
            this->_objects[')'] = &FileMapEntity::_HighGreenWallUp;
            this->_objects['{'] = &FileMapEntity::_GarbageSpawnerDown;
            this->_objects['}'] = &FileMapEntity::_GarbageSpawnerUp;
            this->_objects['m'] = &FileMapEntity::_LowMovingMissileLauncherMob;
            this->_objects['M'] = &FileMapEntity::_HighMovingMissileLauncherMob;
            this->_objects['t'] = &FileMapEntity::_LowFixedMissileLauncherMob;
            this->_objects['T'] = &FileMapEntity::_HighFixedMissileLauncherMob;
            this->_objects['w'] = &FileMapEntity::_WeakMob;
            this->_objects['r'] = &FileMapEntity::_FrontLittleRobotMob;
            this->_objects['a'] = &FileMapEntity::_BackLittleRobotMob;
            this->_objects['0'] = &FileMapEntity::_ForceBonus;
            this->_objects['1'] = &FileMapEntity::_SpeedBonus;
            this->_objects['2'] = &FileMapEntity::_MissileBonus;
            this->_objects['3'] = &FileMapEntity::_FlameBonus;
            this->_objects['4'] = &FileMapEntity::_LaserBonus;
            this->_objects['5'] = &FileMapEntity::_DnaBonus;
            this->_objects['!'] = &FileMapEntity::_Boss1;

            float t = this->_game.GetElapsedTime();
            float step = 64.0f / Game::WALL_SPEED;
            size_t pos = 0;
            char buf[4096];

            std::ifstream file(filepath.c_str());
            if (!file.good())
            {
                Log::E("Could not open file " + filepath + ".");
                return;
            }
            file.getline(buf, 4096);
            std::string levelName(buf, file.gcount());
            if (levelName.size() > 0)
            {
                this->_nameText = new TextEntity<GameEntity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7);
                this->_nameText->SetText("Normal: " + levelName);
                this->_nameText->SetPosition(95, Game::HEIGHT + 8, 250);
            }
            while (file.good())
            {
                file.getline(buf, 4096);
                std::string line(buf, file.gcount());
                std::string::iterator it = line.begin();
                std::string::iterator itEnd = line.end();
                for (; it != itEnd; ++it)
                    if (this->_objects.count(*it) == 1)
                        this->_RegisterEvent(t + step * pos, b00st::bind(this->_objects[*it], *this));
                ++pos;
            }
        }

        FileMapEntity::~FileMapEntity()
        {
            delete this->_nameText;
        }

        void FileMapEntity::_LowWallDown()
        {
            int res = Resources::WALL1_DOWN_64x16_1;
            float r = this->_game.R();
            if (r > 0.66)
                res = Resources::WALL1_DOWN_64x16_2;
            else if (r > 0.33)
                res = Resources::WALL1_DOWN_64x16_3;
            new WallEntity(this->_game, res, false, 64, 16);
        }

        void FileMapEntity::_LowWallUp()
        {
            int res = Resources::WALL1_UP_64x16_1;
            float r = this->_game.R();
            if (r > 0.66)
                res = Resources::WALL1_UP_64x16_2;
            else if (r > 0.33)
                res = Resources::WALL1_UP_64x16_3;
            new WallEntity(this->_game, res, true, 64, 16);
        }

        void FileMapEntity::_HighWallDown()
        {
            new WallEntity(this->_game, Resources::WALL1_DOWN_64x48_1, false, 64, 48);
        }

        void FileMapEntity::_HighWallUp()
        {
            new WallEntity(this->_game, Resources::WALL1_UP_64x48_1, true, 64, 48);
        }

        void FileMapEntity::_LowGreenWallDown()
        {
            new WallEntity(this->_game, Resources::WALL2_DOWN_64x16_1, false, 64, 16);
        }

        void FileMapEntity::_LowGreenWallUp()
        {
            new WallEntity(this->_game, Resources::WALL2_UP_64x16_1, true, 64, 16);
        }

        void FileMapEntity::_HighGreenWallDown()
        {
            new WallEntity(this->_game, Resources::WALL2_DOWN_64x48_1, false, 64, 48);
        }

        void FileMapEntity::_HighGreenWallUp()
        {
            new WallEntity(this->_game, Resources::WALL2_UP_64x48_1, true, 64, 48);
        }

        void FileMapEntity::_GarbageSpawnerDown(void)
        {
            new GarbageSpawnerEntity(this->_game, false);
        }

        void FileMapEntity::_GarbageSpawnerUp(void)
        {
            new GarbageSpawnerEntity(this->_game, true);
        }

        void FileMapEntity::_LowMovingMissileLauncherMob()
        {
            new MissileLauncherMobEntity(this->_game, 212, true);
        }

        void FileMapEntity::_HighMovingMissileLauncherMob()
        {
            new MissileLauncherMobEntity(this->_game, 180, true);
        }

        void FileMapEntity::_LowFixedMissileLauncherMob()
        {
            new MissileLauncherMobEntity(this->_game, 212, false);
        }

        void FileMapEntity::_HighFixedMissileLauncherMob()
        {
            new MissileLauncherMobEntity(this->_game, 180, false);
        }

        void FileMapEntity::_WeakMob()
        {
            new WeakMobEntity(this->_game, 60 + (this->_nbWeakMob % 4) * 20.0f);
            ++this->_nbWeakMob;
        }

        void FileMapEntity::_FrontLittleRobotMob()
        {
            new LittleRobotMobEntity(this->_game, Game::HEIGHT / 2 - 50 + (this->_nbLittleRobotMob % 10) * 10.0f);
            ++this->_nbLittleRobotMob;
        }

        void FileMapEntity::_BackLittleRobotMob()
        {
            new LittleRobotMobEntity(this->_game, Game::HEIGHT / 2 - 50 + (this->_nbLittleRobotMob % 10) * 10.0f, true);
            ++this->_nbLittleRobotMob;
        }

        void FileMapEntity::_ForceBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, Game::HEIGHT / 2 - 50 + (this->_nbBonus % 10) * 10.0f, BonusInteraction::FORCE, Resources::BONUS_FORCE);
            ++this->_nbBonus;
        }

        void FileMapEntity::_SpeedBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, Game::HEIGHT / 2 - 50 + (this->_nbBonus % 10) * 10.0f, BonusInteraction::SPEED, Resources::BONUS_SPEED);
            ++this->_nbBonus;
        }

        void FileMapEntity::_MissileBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, Game::HEIGHT / 2 - 50 + (this->_nbBonus % 10) * 10.0f, BonusInteraction::FORCE_EXPLOSIVE, Resources::BONUS_FORCE_EXPLOSIVE);
            ++this->_nbBonus;
        }

        void FileMapEntity::_FlameBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, Game::HEIGHT / 2 - 50 + (this->_nbBonus % 10) * 10.0f, BonusInteraction::FORCE_FLAME_THROWER, Resources::BONUS_FORCE_FLAME_THROWER);
            ++this->_nbBonus;
        }

        void FileMapEntity::_LaserBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, Game::HEIGHT / 2 - 50 + (this->_nbBonus % 10) * 10.0f, BonusInteraction::FORCE_BOING_LASER, Resources::BONUS_FORCE_BOING_LASER);
            ++this->_nbBonus;
        }

        void FileMapEntity::_DnaBonus(void)
        {
            new BonusCarrierMobEntity(this->_game, Game::HEIGHT / 2 - 50 + (this->_nbBonus % 10) * 10.0f, BonusInteraction::FORCE_DNA_STYLE, Resources::BONUS_FORCE_DNA_STYLE);
            ++this->_nbBonus;
        }

        void FileMapEntity::_Boss1(void)
        {
            new Boss1Entity(this->_game);
        }

    }
}


