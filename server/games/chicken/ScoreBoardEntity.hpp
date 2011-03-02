
#ifndef SCOREBOARDENTITY_HPP_
# define SCOREBOARDENTITY_HPP_

#include <map>

#include "Game.hpp"
#include "Entity.hpp"
#include "TextEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class ScoreBoardEntity : public Entity
        {
        private:
            struct Score
            {
                Score(Game& game)
                    : isNew(true),
                    hasChanged(true),
                    score(0),
                    textScore(game, game.GetResourceManager().GetResourceId(Game::FONT), 6.5),
                    textNick(game, game.GetResourceManager().GetResourceId(Game::FONT), 6.5)
                {
                }

                ~Score(void)
                {
                }

                bool isNew;
                bool hasChanged;
                uint32_t score;
                String playerNick;
                TextEntity textScore;
                TextEntity textNick;
            };

        public:
            explicit ScoreBoardEntity(Game& game);
            ~ScoreBoardEntity(void);

            virtual void Run(float time);

        private:
            std::map<uint16_t, Score*> _scores;

        };

    }
}

#endif // !SCOREBOARDENTITY_HPP_
