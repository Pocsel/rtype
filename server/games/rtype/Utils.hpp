
#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {
        namespace Utils
        {
            ShipEntity* GetNearestShipEntity(Game const& game, Point const& pos);
            MonsterEntity* GetNearestMonsterEntity(Game const& game, Point const& pos);
        }
    }
}


#endif
