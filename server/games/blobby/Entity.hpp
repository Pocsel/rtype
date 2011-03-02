
#ifndef ENTITY_HPP_
# define ENTITY_HPP_

#include "Common2Entity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class Entity : public Common2Entity<Entity, Game>
        {
        public:
            explicit Entity(Game& game, String const& name, uint16_t playerId = 0);
            virtual ~Entity();

            // Interactions
        };

    }
}

#endif // !ENTITY_HPP_
