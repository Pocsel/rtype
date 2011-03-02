#include "Common2ManagerEntity.cpp"

#include "Entity.hpp"
#include "Game.hpp"
#include "PlayerEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        template class Common2ManagerEntity<Entity, Game, PlayerEntity>;

    }
}
