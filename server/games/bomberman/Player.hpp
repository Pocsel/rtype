#ifndef __GAMEPLAYER_HPP__
#define __GAMEPLAYER_HPP__

#include "BasicPlayer.hpp"
#include "PlayerEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Entity;
        class Game;
        template<typename Entity, typename Player> class BasicGame;
        class ITcpSocketProxy;

        class Player :
            public BasicPlayer
        {
            public:
                explicit Player(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<Entity, Player>& game);
                ~Player();
                int GetScore() const;
                void AddToScore(int val);
            private:
                Game& _game;
                PlayerEntity* _player;
                int _score;
        };

    }
}

#endif

