#include "Game.hpp"
#include "MonsterGeneratorEntity.hpp"
#include "WeakMobEntity.hpp"
#include "LittleRobotMobEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        MonsterGeneratorEntity::MonsterGeneratorEntity(Game& game, float delay, float number, Type type) :
            GameEntity(game, "Monster Generator"), delay(delay), number(number), type(type), _nextSpawn(0)
        {
            if (this->delay == 0)
                this->delay = 0.1f;
            if (this->delay < 0)
                this->delay = -this->delay;

            this->_spawns.push_back(&MonsterGeneratorEntity::_SpawnWeak);
            this->_spawns.push_back(&MonsterGeneratorEntity::_SpawnLittleRobot);
            this->_spawns.push_back(&MonsterGeneratorEntity::_SpawnLittleRobotReverse);
        }

        MonsterGeneratorEntity::~MonsterGeneratorEntity()
        {
        }

        void MonsterGeneratorEntity::Run(float time)
        {
            if (time >= this->_nextSpawn)
            {
                for (int i = 0 ; i < this->number ; ++i)
                    (this->*this->_spawns[this->type])();
                this->_nextSpawn = time + this->delay + this->_game.R();
            }
        }

        void MonsterGeneratorEntity::SpawnNow(void)
        {
            this->_nextSpawn = 0;
        }

        void MonsterGeneratorEntity::_SpawnWeak(void)
        {
            new WeakMobEntity(this->_game, Game::HEIGHT / 5 + this->_game.R() * Game::HEIGHT * 3/5);
        }

        void MonsterGeneratorEntity::_SpawnLittleRobot(void)
        {
            new LittleRobotMobEntity(this->_game, Game::HEIGHT / 5 + this->_game.R() * Game::HEIGHT * 3/5);
        }

        void MonsterGeneratorEntity::_SpawnLittleRobotReverse(void)
        {
            new LittleRobotMobEntity(this->_game, Game::HEIGHT / 5 + this->_game.R() * Game::HEIGHT * 3/5, true);
        }

    }
}

