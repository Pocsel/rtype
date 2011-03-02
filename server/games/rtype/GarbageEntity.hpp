
#ifndef GARBAGEENTITY_HPP_
# define GARBAGEENTITY_HPP_

#include "GameEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class GarbageEntity : public GameEntity
        {
        private:
            enum
            {
                WIDTH = 64,
                HEIGHT = 32,
                MAX_FRAME = 3
            };
        public:
            explicit GarbageEntity(Game& game, int resourceLocalId, bool up, float width, float height, float posX);
            ~GarbageEntity(void);

            virtual void GenerateInteractions(float time);
            virtual void Run(float time);

        private:
            Item _sprite;
            InteractionPtr _interaction;

            float _width;
            float _height;
        };

    }
}


#endif // !GARBAGEENTITY_HPP_
