#include "ParticleGeneratorEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        ParticleGeneratorEntity::ParticleGeneratorEntity(Game& game) :
            GameEntity(game, "Particle generator"), _nextSpawn(0)
        {
        }

        ParticleGeneratorEntity::~ParticleGeneratorEntity()
        {
        }

        void ParticleGeneratorEntity::Run(float time)
        {
            if (time >= this->_nextSpawn)
            {
                this->_nextSpawn = time + this->_game.R() * 0.2f + 0.3f;
                Item p;
                p.SetLuaId(this->_game.GetResourceManager().GetResourceId(Resources::LUA_PARTICLE));
                p.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::PARTICLE1));
                p.SetPositionX(Game::WIDTH - 1);
                p.SetPositionY(this->_game.R() * Game::HEIGHT);
                p.SetPositionZ(10);
                p.SetDisapear(true);
                this->_game.GetItemManager().SendItem(p);
            }
        }

    }
}

