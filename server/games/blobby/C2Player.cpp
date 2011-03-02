#include "Common2Player.cpp"

#include "Entity.hpp"
#include "Game.hpp"
#include "PlayerEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        template class Common2Player<Entity, Game, PlayerEntity>;

    }
}
