#ifndef __BONUSENTITY_HPP__
#define __BONUSENTITY_HPP__

#include "Entity.hpp"
#include "Item.hpp"
#include "BonusInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class BonusEntity :
            public Entity
        {
            public:
                enum Type
                {
                    BOMB,
                    POWER
                };
                explicit BonusEntity(Game& game, float x, float y, int type);
                ~BonusEntity();
                virtual void GenerateInteractions(float time);
                virtual void Run(float time);
                bool Interact(BombInteraction&);
            private:
                Item _sprite;
                InteractionPtr _bonus;
        };

    }
}

#endif

