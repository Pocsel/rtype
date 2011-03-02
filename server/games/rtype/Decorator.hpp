
#ifndef DECORATOR_HPP_
# define DECORATOR_HPP_

#include "MainGame.hpp"
#include "Game.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Decorator
        {
        public:

            template<typename T>
            static inline void Explosion(int id, T& entity)
            {
                Item i;
                i.SetResourceId(entity._game.GetResourceManager().GetResourceId(id));
                i.SetPositionX(entity._sprite.GetPositionX());
                i.SetPositionY(entity._sprite.GetPositionY());
                i.SetSpeedX(-Game::WALL_SPEED);
                i.SetLifeTimeCycles(1);
                i.SetPositionZ(130);
                entity._game.GetItemManager().SendItem(i);
            }

            template<typename Game>
            static inline void PlaySound(Game& game, int id, uint16_t playerId = 0)
            {
                Item i;
                i.SetResourceId(game.GetResourceManager().GetResourceId(id));
                i.SetLifeTimeCycles(1);
                if (playerId)
                    i.SetPlayerId(playerId);
                game.GetItemManager().SendItem(i);
            }

        };

    }
}

#endif // !DECORATOR_HPP_
