
#include <list>
#include "Utils.hpp"

namespace Gmgp
{
    namespace Server
    {
        namespace Utils
        {
            ShipEntity* GetNearestShipEntity(Game const& game, Point const& pos)
            {
                std::list<ShipEntity*>::const_iterator it = game.GetListOfPlayerShips().begin();
                std::list<ShipEntity*>::const_iterator ite = game.GetListOfPlayerShips().end();
                ShipEntity* nearestPlayer = 0;
                if (it != ite)
                {
                    float minDist = 1e20f;
                    for (; it != ite; ++it)
                        if ((*it)->GetState() == ShipEntity::ALIVE && (*it)->GetPosition().GetSquaredDistance(pos) < minDist)
                        {
                            nearestPlayer = *it;
                            minDist = nearestPlayer->GetPosition().GetSquaredDistance(pos);
                        }
                }
                return nearestPlayer;
            }

            MonsterEntity* GetNearestMonsterEntity(Game const& game, Point const& pos)
            {
                std::list<MonsterEntity*>::const_iterator it = game.GetListOfMonsters().begin();
                std::list<MonsterEntity*>::const_iterator ite = game.GetListOfMonsters().end();
                MonsterEntity* nearestMonster = 0;
                if (it != ite)
                {
                    float minDist = 1e20f;
                    for (; it != ite; ++it)
                        if ((*it)->GetPosition().GetSquaredDistance(pos) < minDist)
                        {
                            nearestMonster = *it;
                            minDist = nearestMonster->GetPosition().GetSquaredDistance(pos);
                        }
                }
                return nearestMonster;
            }
        }
    }
}
