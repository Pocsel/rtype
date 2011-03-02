#ifndef __PLAYERENTITY_HPP__
#define __PLAYERENTITY_HPP__

#include <map>
#include "GameEntity.hpp"
#include "Item.hpp"
#include "TextEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MainGame;

        class PlayerEntity : public GameEntity
        {
            public:
                explicit PlayerEntity(Game& game, uint16_t playerId, String const& nick);
                ~PlayerEntity();
                virtual void Run(float time);

            private:
//                void _CreateScoreboard();
//                void _DestroyScoreboard();
//                void _UpdateScoreboard();
//                bool _scoreboardOpen;
//                Item _scoreboard;
//                std::list<TextEntity<GameEntity, Game>*> _nicks;
//                std::list< std::pair<uint16_t, TextEntity<GameEntity, Game>*> > _scores;
        };

    }
}

#endif

