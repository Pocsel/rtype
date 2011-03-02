#include "Common2PlayerEntity.cpp"

#include "Entity.hpp"
#include "Game.hpp"
#include "PlayerEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        template class Common2PlayerEntity<Entity, Game, PlayerEntity>;

    }
}

