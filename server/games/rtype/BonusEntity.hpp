
#ifndef BONUSENTITY_HPP_
# define BONUSENTITY_HPP_

#include "GameEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class BonusEntity : public GameEntity
        {
        private:
            enum
            {
                RADIUS = 16,
            };
        public:
            explicit BonusEntity(Game& game, int type, int spriteId, float x, float y);
            virtual ~BonusEntity();

            virtual void GenerateInteractions(float time);
            virtual void Run(float time);

        protected:
            Item _sprite;
            InteractionPtr _interaction;
        };

    }
}

#endif // !BONUSENTITY_HPP_
