#ifndef __CHICKENGENERATORENTITY_HPP__
#define __CHICKENGENERATORENTITY_HPP__

#include "Entity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ChickenGeneratorEntity : public Entity
        {
        public:
            explicit ChickenGeneratorEntity(Game& game, uint16_t playerId);
            ~ChickenGeneratorEntity(void);
            virtual void Run(float time);

        private:
            float _nextSpawn;
        };

    }
}

#endif

