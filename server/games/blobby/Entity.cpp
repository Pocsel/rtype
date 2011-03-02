
#include "Entity.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        Entity::Entity(Game& game, String const& name, uint16_t playerId)
            : Common2Entity<Entity, Game>(game, name, playerId)
        {
        }

        Entity::~Entity()
        {
        }

    }
}

