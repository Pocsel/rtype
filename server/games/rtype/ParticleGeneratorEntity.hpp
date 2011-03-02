#ifndef __PARTICLEGENERATORENTITY_HPP__
#define __PARTICLEGENERATORENTITY_HPP__

#include "GameEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class ParticleGeneratorEntity : public GameEntity
        {
            public:
                explicit ParticleGeneratorEntity(Game& game);
                ~ParticleGeneratorEntity();
                virtual void Run(float time);
            private:
                float _nextSpawn;
        };

    }
}

#endif

