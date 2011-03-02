#ifndef __GAMEPLAYER_HPP__
#define __GAMEPLAYER_HPP__

#include "BasicPlayer.hpp"

namespace Gmgp
{
    namespace Server
    {

        class PlayerEntity;

        class GameEntity;
        class Game;
        template<typename Entity, typename GamePlayer> class BasicGame;
        class ITcpSocketProxy;

        class GamePlayer :
            public BasicPlayer
        {
            public:
                explicit GamePlayer(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<GameEntity, GamePlayer>& game);
                ~GamePlayer();
                size_t GetScore() const;
                void AddScore(size_t score);

            private:
                Game& _game;
                PlayerEntity* _player;
                size_t _score;
        };

    }
}

#endif

