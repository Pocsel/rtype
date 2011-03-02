#include "ManagerEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "BombInteraction.hpp"
#include "WallEntity.hpp"
#include "Decorator.hpp"

namespace Gmgp
{
    namespace Server
    {

        ManagerEntity::ManagerEntity(Game& game) :
            Entity(game, "Manager"),
            _started(false),
            _lastNbOfPlayers(0),
            _spawnStart(0),
            _mapDestroyed(false),
            _bombInteraction(new BombInteraction(0))
        {
            this->_bg.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BACKGROUND_IG));
            this->_bg.SetPositionX(Game::FULLWIDTH / 2);
            this->_bg.SetPositionY(Game::FULLHEIGHT / 2);
            this->_bg.SetPositionZ(0);
            this->_game.GetItemManager().AddItem(&this->_bg);
            // top
            this->_spawns.push_back(std::pair<int, int>(7, 1));
            this->_spawns.push_back(std::pair<int, int>(19, 1));
            this->_spawns.push_back(std::pair<int, int>(31, 1));
            // bottom
            this->_spawns.push_back(std::pair<int, int>(7, 25));
            this->_spawns.push_back(std::pair<int, int>(19, 25));
            this->_spawns.push_back(std::pair<int, int>(31, 25));
            // left
            this->_spawns.push_back(std::pair<int, int>(1, 7));
            this->_spawns.push_back(std::pair<int, int>(1, 19));
            // right
            this->_spawns.push_back(std::pair<int, int>(37, 7));
            this->_spawns.push_back(std::pair<int, int>(37, 19));
        }

        ManagerEntity::~ManagerEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_bg);
            if (this->_started)
                this->_game.GetItemManager().RemoveItem(&this->_music);
            this->_ClearPanel();
        }

        void ManagerEntity::_ClearPanel()
        {
            std::list<Score*>::iterator it = this->_scores.begin();
            std::list<Score*>::iterator itEnd = this->_scores.end();
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

        void ManagerEntity::_UpdatePanel()
        {
            this->_ClearPanel();
            float x = Game::CASE_SIZE;
            std::list<PlayerEntity*> const& list = this->_game.GetListOfPlayers();
            std::list<PlayerEntity*>::const_iterator it = list.begin();
            std::list<PlayerEntity*>::const_iterator itEnd = list.end();
            try
            {
                for (; it != itEnd; ++it)
                {
                    Player& p = this->_game.GetPlayerManager().GetPlayer((*it)->GetPlayerId());
                    Score* s = new Score;
                    s->icon = new Item;
                    s->icon->SetPositionX(x);
                    s->icon->SetPositionY(16);
                    s->icon->SetPositionZ(250);
                    s->icon->SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::P1_ICON + (*it)->GetColorId() % 8));
                    this->_game.GetItemManager().AddItem(s->icon);
                    s->score = p.GetScore();
                    s->scoreText = new TextEntity<Entity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7);
                    s->scoreText->SetText(String(s->score));
                    s->scoreText->SetPosition(x + Game::CASE_SIZE, 30, 250);
                    s->nick = new TextEntity<Entity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7);
                    s->nick->SetText(p.GetNick());
                    s->nick->SetPosition(x + Game::CASE_SIZE, 16, 250);
                    this->_scores.push_back(s);
                    x += 75;
                }
            }
            catch (std::exception&)
            {
            }
        }

        void ManagerEntity::_SpawnPlayers()
        {
            Log::D("Spawning players...");
            std::vector< std::pair<int, int> > spawns = this->_spawns;
            size_t nbPlayers = 0;
            std::list<PlayerEntity*> const& list = this->_game.GetListOfPlayers();
            std::list<PlayerEntity*>::const_iterator it = list.begin();
            std::list<PlayerEntity*>::const_iterator itEnd = list.end();
            for (; it != itEnd; ++it)
            {
                if (nbPlayers > 7)
                    break;
                int spawn = static_cast<int>(this->_game.R() * 1000.0f) % spawns.size();
                (*it)->Spawn(spawns[spawn].first, spawns[spawn].second);
                spawns.erase(spawns.begin() + spawn);
                ++nbPlayers;
            }
        }

        void ManagerEntity::_SpawnMap()
        {
            Log::D("Spawning map...");
            for (int y = 1; y < Game::Y_SIZE - 1; ++y)
                for (int x = 1; x < Game::X_SIZE - 1; ++x)
                    if (x % 2 != 0 || y % 2 != 0)
                    {
                        bool isInvalid = false;
                        std::vector< std::pair<int, int> >::iterator it = this->_spawns.begin();
                        std::vector< std::pair<int, int> >::iterator itEnd = this->_spawns.end();
                        for (; it != itEnd; ++it)
                            if (it->first == x && it->second == y)
                            {
                                isInvalid = true;
                                break;
                            }
                        if (!isInvalid && this->_game.R() > 0.66)
                            new WallEntity(this->_game, x, y);
                    }

        }

        void ManagerEntity::_DestroyMap()
        {
            Log::D("Destroying map...");
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_bombInteraction,
                    Circle(Game::FULLWIDTH / 2, Game::FULLHEIGHT / 2, 4096));
        }

        void ManagerEntity::Run(float time)
        {
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
                std::list<Score*>::iterator listIt = this->_scores.begin();
                std::list<PlayerEntity*> const& list = this->_game.GetListOfPlayers();
                std::list<PlayerEntity*>::const_iterator it = list.begin();
                std::list<PlayerEntity*>::const_iterator itEnd = list.end();
                try
                {
                    for (; it != itEnd; ++it)
                    {
                        if ((*listIt)->score != this->_game.GetPlayerManager().GetPlayer((*it)->GetPlayerId()).GetScore())
                        {
                            updatePanel = true;
                            break;
                        }
                        ++listIt;
                        if (listIt == this->_scores.end())
                            break;
                    }
                }
                catch (std::exception&)
                {
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
                    this->_SpawnMap();
                    this->_SpawnPlayers();
                    this->_spawnStart = 0;
                    this->_RestartMusic();
                    this->_started = true;
                }
            }
            else
            {
                // rounds
                if (this->_scores.size() >= 2)
                {
                    int nbAlive = 0;
                    std::list<PlayerEntity*> const& list = this->_game.GetListOfPlayers();
                    std::list<PlayerEntity*>::const_iterator it = list.begin();
                    std::list<PlayerEntity*>::const_iterator itEnd = list.end();
                    uint16_t id = 0;
                    for (; it != itEnd; ++it)
                        if ((*it)->IsAlive())
                        {
                            id = (*it)->GetPlayerId();
                            ++nbAlive;
                        }
                    if (nbAlive <= 1)
                    {
                        if (id != 0)
                        {
                            try
                            {
                                this->_game.GetPlayerManager().GetPlayer(id).AddToScore(5);
                            }
                            catch (std::exception&)
                            {
                            }
                            Decorator::PlaySound(Resources::WA_WIN, this->_game);
                        }
                        this->_spawnStart = time;
                        Item ticker;
                        ticker.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::COUNTER));
                        ticker.SetPositionX(Game::FULLWIDTH / 2);
                        ticker.SetPositionY(Game::FULLHEIGHT / 2);
                        ticker.SetPositionZ(250);
                        ticker.SetLifeTimeCycles(1);
                        this->_game.GetItemManager().SendItem(ticker);
                        this->_mapDestroyed = false;
                    }
                }
            }
        }

        void ManagerEntity::_RestartMusic(void)
        {
            if (this->_started)
                this->_game.GetItemManager().RemoveItem(&this->_music);
            int i = static_cast<int>(Resources::WA_INGAME1 + this->_game.R() * 3);
            if (i > Resources::WA_INGAME4)
                i = Resources::WA_INGAME4;
            this->_music.SetResourceId(this->_game.GetResourceManager().GetResourceId(i));
            this->_game.GetItemManager().AddItem(&this->_music);
        }

    }
}

