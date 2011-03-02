#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "BasicPlayer.hpp"
#include "ChickenGeneratorEntity.hpp"
#include "PlayerEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;
        template<typename Entity, typename Player> class BasicGame;

        class Player :
            public BasicPlayer
        {
            public:
                explicit Player(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, Game& game);
                explicit Player(uint16_t id, String const& nick, ITcpSocketProxy* socketProxy, BasicGame<Entity, Player>& game);
                ~Player();

                void IncrementScore(uint32_t score);
                uint32_t GetScore(void) const;

                void PutBigDamage(float posX, float posY);

            private:
                Game& _game;
                ChickenGeneratorEntity* _generator;
                PlayerEntity* _entity;
                uint32_t _score;
        };

    }
}

#endif

