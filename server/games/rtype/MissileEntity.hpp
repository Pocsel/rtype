#ifndef __MISSILEENTITY_HPP__
#define __MISSILEENTITY_HPP__

#include "GameEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class MissileEntity : public GameEntity
        {
            public:
                enum Type
                {
                    UP,
                    CENTER,
                    DOWN
                };
                explicit MissileEntity(Game& game, float x, float y, int type, float speedY = -200);
                ~MissileEntity();
                virtual void Run(float time);
                bool Interact(ShieldInteraction&);
                bool Interact(WallInteraction&);
                bool Interact(ShipInteraction&);
            private:
                void _Explode(bool damage);
                Item _sprite;
                int _type;
                float _timeSave;
                bool _dirSet;
                bool _launched;
                int _nbSmoke;
                InteractionPtr _damage;
                bool _dead;
        };

    }
}

#endif

