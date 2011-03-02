
#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include "Common2Player.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Entity;
        class PlayerEntity;

        typedef Common2Player<Entity, Game, PlayerEntity> Player;

    }
}

#endif // !PLAYER_HPP_
