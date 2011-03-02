
#ifndef CHICKENENTITY_HPP_
# define CHICKENENTITY_HPP_

#include "Entity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ChickenEntity : public Entity
        {
        public:
            explicit ChickenEntity(Game& game, bool super = false);
            ~ChickenEntity(void);

            virtual void Run(float time);

            // Interactions
            virtual bool Interact(DamageInteraction& interaction);

        private:
            void _Explode(int resourceLocalId);
            void _CreateFeathers(void);
            void _MakeSound(int resourceLocalId);

            Item _sprite;
            int _deathLocalId;
            bool _superChicken;
        };

    }
}

#endif // !CHICKENENTITY_HPP_
