
#include "ScoreBoardEntity.hpp"
#include "Game.hpp"
#include "TextEntity.hpp"
#include "PlayerManager.hpp"

namespace Gmgp
{
    namespace Server
    {

        ScoreBoardEntity::ScoreBoardEntity(Game& game) : Entity(game, "Score Board 5k")
        {
        }

        ScoreBoardEntity::~ScoreBoardEntity(void)
        {
                for (std::map<uint16_t, Score*>::iterator it = this->_scores.begin(),
                     ite = this->_scores.end() ; it != ite ; ++it)
                {
                    delete it->second;
                }
        }

        void ScoreBoardEntity::Run(float)
        {
            std::list<uint16_t> playerIds = this->_game.GetPlayerManager().GetPlayerIdList();
            std::list<uint16_t> removablePlayers;

            try
            {
                for (std::map<uint16_t, Score*>::iterator it = this->_scores.begin(),
                     ite = this->_scores.end() ; it != ite ; ++it)
                {
                    bool checked = false;
                    for (std::list<uint16_t>::iterator pit = playerIds.begin(),
                         pite = playerIds.end() ; pit != pite ; ++pit)
                    {
                        if (*pit == it->first)
                        {
                            uint32_t score = this->_game.GetPlayerManager().GetPlayer(it->first).GetScore();
                            if (it->second->score != score)
                            {
                                it->second->score = score;
                                it->second->hasChanged = true;
                            }
                            playerIds.erase(pit);
                            checked = true;
                            break;
                        }
                    }
                    if (checked == false)
                        removablePlayers.push_back(it->first);
                }

                bool updateList = false;
                for (std::list<uint16_t>::iterator it = removablePlayers.begin(),
                     ite = removablePlayers.end() ; it != ite ; ++it)
                {
                    updateList = true;
                    delete this->_scores[*it];
                    this->_scores.erase(*it);
                }

                for (std::list<uint16_t>::iterator it = playerIds.begin(),
                     ite = playerIds.end() ; it != ite ; ++it)
                {
                    this->_scores[*it] = new Score(this->_game);
                    this->_scores[*it]->score = this->_game.GetPlayerManager().GetPlayer(*it).GetScore();
                    this->_scores[*it]->playerNick = this->_game.GetPlayerManager().GetPlayer(*it).GetNick();
                    updateList = true;
                }

                uint32_t posY = 12;

                for (std::map<uint16_t, Score*>::iterator it = this->_scores.begin(),
                     ite = this->_scores.end() ; it != ite ; ++it)
                {
                    if (it->second->hasChanged || updateList)
                    {
                        Score* score = it->second;
                        score->hasChanged = false;
                        score->textScore.SetText(": " + String(score->score));
                        score->textScore.SetPosition(90, posY, 230);
                        if (score->isNew || updateList)
                        {
                            score->isNew = false;
                            score->textNick.SetText(score->playerNick);
                            score->textNick.SetPosition(12, posY, 230);
                        }
                    }
                    posY += 12;
                }

            }
            catch (std::exception&)
            {
            }

        }

    }
}
