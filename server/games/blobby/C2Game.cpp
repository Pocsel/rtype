#include "Common2Game.cpp"

#include "Entity.hpp"
#include "PlayerEntity.hpp"
#include "ManagerEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        template class Common2Game<Entity, Game, PlayerEntity, ManagerEntity, 40, 320, 240, 2>;

    }
}

