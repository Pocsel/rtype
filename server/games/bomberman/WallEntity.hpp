#ifndef __WALLENTITY_HPP__
#define __WALLENTITY_HPP__

#include "Entity.hpp"
#include "Item.hpp"
#include "BombInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class WallEntity :
            public Entity
        {
            public:
                explicit WallEntity(Game& game, int x, int y);
                ~WallEntity();
                virtual void Run(float time);
                virtual bool Interact(BombInteraction& i);
            private:
                Item _sprite;
                bool _noBonus;
        };

    }
}

#endif

