
#ifndef BACKGROUNDENTITY_HPP_
# define BACKGROUNDENTITY_HPP_

#include "Entity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class BackgroundEntity : public Entity
        {
        public:
            explicit BackgroundEntity(Game& game);
            ~BackgroundEntity(void);

        private:
            Item _sprite;
            Item _music;
        };

    }
}

#endif // !BACKGROUNDENTITY_HPP_
