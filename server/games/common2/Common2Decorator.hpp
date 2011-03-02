
#ifndef COMMON2DECORATOR_HPP_
# define COMMON2DECORATOR_HPP_

#include "Game.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Common2Decorator
        {
        public:

            template<typename E>
                static void Explosion(int id, E& entity)
                {
                    Item i;
                    i.SetResourceId(entity._game.GetResourceManager().GetResourceId(id));
                    i.SetPositionX(entity._sprite.GetPositionX());
                    i.SetPositionY(entity._sprite.GetPositionY());
                    i.SetSpeedX(0);
                    i.SetLifeTimeCycles(1);
                    i.SetPositionZ(130);
                    entity._game.GetItemManager().SendItem(i);
                }

            template<typename G>
                static void PlaySound(int id, G& game)
                {
                    Item i;
                    i.SetResourceId(game.GetResourceManager().GetResourceId(id));
                    i.SetLifeTimeCycles(1);
                    game.GetItemManager().SendItem(i);
                }

        };

    }
}

#endif // !DECORATOR_HPP_
