#ifndef __PLAYERENTITY_HPP__
#define __PLAYERENTITY_HPP__

#include "Entity.hpp"
#include "DamageInteraction.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class IGame;

        class PlayerEntity : public Entity
        {
        public:
            explicit PlayerEntity(Game& game, uint16_t id);
            ~PlayerEntity(void);
            virtual void Run(float time);

            void PutBigDamage(float posX, float posY);

        private:
            Item _visor;
            InteractionPtr _damage;
            InteractionPtr _bigDamage;
        };

    }
}

#endif

