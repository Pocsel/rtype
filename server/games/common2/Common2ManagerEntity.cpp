#include "Common2ManagerEntity.hpp"
#include "Common2TextEntity.hpp"
#include "Common2Game.hpp"
#include "Common2Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        template<typename E, typename G, typename PE>
            Common2ManagerEntity<E, G, PE>::Common2ManagerEntity(G& game, size_t nbPlayers) :
                E(game, "Manager"),
                _nbPlayers(nbPlayers),
                _bgReady(false),
                _started(false),
                _lastNbOfPlayers(0),
                _spawnStart(0),
                _mapDestroyed(false)
        {
        }

        template<typename E, typename G, typename PE>
            Common2ManagerEntity<E, G, PE>::~Common2ManagerEntity()
            {
                this->_game.GetItemManager().RemoveItem(&this->_bg);
                this->_ClearPanel();
            }

        template<typename E, typename G, typename PE>
            void Common2ManagerEntity<E, G, PE>::_ClearPanel()
            {
                typename std::list<Score*>::iterator it = this->_scores.begin();
                typename std::list<Score*>::iterator itEnd = this->_scores.end();
                for (; it != itEnd; ++it)
                {
                    this->_game.GetItemManager().RemoveItem((*it)->icon);
                    delete (*it)->icon;
                    delete (*it)->nick;
                    delete (*it)->scoreText;
                    delete *it;
                }
                this->_scores.clear();
            }

        template<typename E, typename G, typename PE>
            void Common2ManagerEntity<E, G, PE>::_UpdatePanel()
            {
                this->_GetBgId();
                this->_ClearPanel();
                float x = 16;
                typename std::list<PE*> const& list = this->_game.GetListOfPlayers();
                typename std::list<PE*>::const_iterator it = list.begin();
                typename std::list<PE*>::const_iterator itEnd = list.end();

                size_t nbPlayers = 0;
                for (; it != itEnd; ++it)
                {
                    if (nbPlayers >= this->_nbPlayers)
                        break;
                    ++nbPlayers;

                    Score* s = new Score;
                    s->icon = new Item;
                    s->icon->SetPositionX(x);
                    s->icon->SetPositionY(16);
                    s->icon->SetPositionZ(250);
                    s->icon->SetResourceId(this->_game.GetResourceManager().GetResourceId(this->_GetIconId() + (*it)->GetColorId() % this->_nbPlayers));
                    this->_game.GetItemManager().AddItem(s->icon);
                    s->score = (*it)->GetScore();
                    s->scoreText = new Common2TextEntity<E, G>(this->_game, this->_game.GetResourceManager().GetResourceId(Common2Resources::FONT), 7);
                    s->scoreText->SetText(String(s->score));
                    s->scoreText->SetPosition(x + 16, 30, 250);
                    s->nick = new Common2TextEntity<E, G>(this->_game, this->_game.GetResourceManager().GetResourceId(Common2Resources::FONT), 7);
                    s->nick->SetText((*it)->GetNick());
                    s->nick->SetPosition(x + 16, 16, 250);
                    this->_scores.push_back(s);
                    x += 75;
                }
            }

        template<typename E, typename G, typename PE>
            void Common2ManagerEntity<E, G, PE>::Run(float time)
            {
                if (this->_bgReady == false)
                {
                    this->_bg.SetResourceId(this->_game.GetResourceManager().GetResourceId(this->_GetBgId()));
                    this->_bg.SetPositionX(G::FULLWIDTH / 2);
                    this->_bg.SetPositionY(G::FULLHEIGHT / 2);
                    this->_bg.SetPositionZ(0);
                    this->_game.GetItemManager().AddItem(&this->_bg);
                    this->_bgReady = true;
                }
                bool updatePanel = false;
                // un joueur arrive
                if (this->_lastNbOfPlayers != this->_game.GetNumberOfPlayers())
                {
                    updatePanel = true;
                    this->_lastNbOfPlayers = this->_game.GetNumberOfPlayers();
                }

                // un joueur a change de score
                if (this->_scores.size() > 0)
                {
                    typename std::list<Score*>::iterator listIt = this->_scores.begin();
                    typename std::list<Score*>::iterator listItEnd = this->_scores.end();
                    typename std::list<PE*> const& list = this->_game.GetListOfPlayers();
                    typename std::list<PE*>::const_iterator it = list.begin();
                    typename std::list<PE*>::const_iterator itEnd = list.end();
                    for (; it != itEnd && listIt != listItEnd; ++it, ++listIt)
                    {
                        if ((*listIt)->score != (*it)->GetScore())
                        {
                            updatePanel = true;
                            break;
                        }
                    }
                }

                // maj du panel
                if (updatePanel)
                    this->_UpdatePanel();

                // spawning
                if (this->_spawnStart > 0)
                {
                    if (time - this->_spawnStart >= 4 && !this->_mapDestroyed)
                    {
                        this->_DestroyMap();
                        this->_mapDestroyed = true;
                    }
                    if (time - this->_spawnStart >= 5)
                    {
                        this->_spawnStart = 0;
                        this->_SpawnMap();
                        if (this->_started)
                            this->_RestartMusic();
                        else
                            this->_StartMusic();
                        this->_started = true;
                    }
                }
                else
                {
                    // rounds
                    if (this->_scores.size() >= 2)
                    {
                        int nbAlive = 0;
                        typename std::list<PE*> const& list = this->_game.GetListOfPlayers();
                        typename std::list<PE*>::const_iterator it = list.begin();
                        typename std::list<PE*>::const_iterator itEnd = list.end();
                        PE* p = 0;
                        for (; it != itEnd; ++it)
                            if ((*it)->IsAlive())
                            {
                                p = *it;
                                ++nbAlive;
                            }
                        if (nbAlive <= 1)
                        {
                            if (p != 0)
                                p->LastAlive();

                            this->_spawnStart = time;
                            Item ticker;
                            ticker.SetResourceId(this->_game.GetResourceManager().GetResourceId(Common2Resources::COUNTER));
                            ticker.SetPositionX(G::FULLWIDTH / 2);
                            ticker.SetPositionY(G::FULLHEIGHT / 2);
                            ticker.SetPositionZ(250);
                            ticker.SetLifeTimeCycles(1);
                            this->_game.GetItemManager().SendItem(ticker);
                            this->_mapDestroyed = false;
                        }
                    }
                }
            }

        template<typename E, typename G, typename PE>
            void Common2ManagerEntity<E, G, PE>::_SpawnMap()
            {
            }

        template<typename E, typename G, typename PE>
            void Common2ManagerEntity<E, G, PE>::_DestroyMap()
            {
            }

        template<typename E, typename G, typename PE>
            void Common2ManagerEntity<E, G, PE>::_StartMusic(void)
            {
            }

        template<typename E, typename G, typename PE>
            void Common2ManagerEntity<E, G, PE>::_RestartMusic(void)
            {
            }

    }
}

