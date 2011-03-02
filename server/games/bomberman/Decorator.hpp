
#ifndef DECORATOR_HPP_
# define DECORATOR_HPP_

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
            static void Explosion(int id, T& entity)
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

            static void PlaySound(int id, Game& game)
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
