
#ifndef BGTILEENTITY_HPP_
# define BGTILEENTITY_HPP_

#include "GameEntity.hpp"
#include "Item.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;

        class BgTileEntity : public GameEntity
        {
            public:
                explicit BgTileEntity(Game& game,
                                      uint16_t resourceId,
                                      float x,
                                      float y,
                                      float width,
                                      float z,
                                      float speed);
                ~BgTileEntity(void);
                virtual void Run(float time);

                void Stop(void);
                void Go(void);

            private:
                Item _sprite;
                float _width;
                float _speed;
        };

    }
}

#endif // !BGTILEENTITY_HPP_
