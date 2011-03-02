#ifndef __LUAMISSILEENTITY_HPP__
#define __LUAMISSILEENTITY_HPP__

#include "GameEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class LuaMissileEntity : public GameEntity
        {
            public:
                explicit LuaMissileEntity(Game& game, float posX, float posY, float speedX, float speedY, float accelX, float accelY);
                ~LuaMissileEntity();
                virtual void Run(float time);
                virtual bool Interact(ShipInteraction&);
                virtual bool Interact(ShieldInteraction&);
                virtual bool Interact(WallInteraction&);
            private:
                void _Explode(bool damage);
                Item _sprite;
                bool _dead;
                InteractionPtr _damage;
        };

    }
}

#endif

