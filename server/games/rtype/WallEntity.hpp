
#ifndef WALLENTITY_HPP_
# define WALLENTITY_HPP_

#include "GameEntity.hpp"
#include "Item.hpp"
#include "WallInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class WallEntity : public GameEntity
        {
        public:
            explicit WallEntity(Game& game, int resourceLocalId, bool up, float width, float height);
            ~WallEntity(void);

            virtual void GenerateInteractions(float time);
            virtual void Run(float time);

            void Stop(void);
            void Go(void);

        protected:
            Item _sprite;
            InteractionPtr _interaction;
            float _width;
            float _height;
        };

    }
}

#endif // !WALLENTITY_HPP_
