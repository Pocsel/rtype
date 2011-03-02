
#ifndef BALLENTITY_HPP_
# define BALLENTITY_HPP_

#include "Entity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class BallEntity
            : public Entity
        {
        private:
            enum
            {
                GRAVITY = 50,
            };
        public:
            BallEntity(Game& game);
            ~BallEntity();

        private:
            Item _ball;
        };

    }
}

#endif // !BALLENTITY_HPP_
