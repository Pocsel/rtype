#include "Game.hpp"
#include "PlayerManager.hpp"
#include "AnimationResourceInfo.hpp"
#include "SoundResourceInfo.hpp"
#include "Resources.hpp"
#include "EnduranceMap1Entity.hpp"
#include "FileMapEntity.hpp"
#include "MainGame.hpp"
#include "BgTileEntity.hpp"
#include "WallEntity.hpp"
#include "ForceEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        Game::Game(uint16_t playerId, int mode)
            : BasicGame<GameEntity, GamePlayer>("R-Type Game", Game::TICKS_TIME, Game::FULLWIDTH, Game::FULLHEIGHT),
            _mainGame(0),
            _creatorId(playerId),
            _map(0),
            _bg(0),
            _mode(mode),
            _room(0),
            _particles(0),
            _enduranceLevel(1),
            _timer(0),
            _mapCounter(0)
        {
            Log::I("R-Type Game created.");
        }

        Game::~Game(void)
        {
            Log::I("R-Type Game destroyed.");
        }

        void Game::Score(uint16_t player, size_t value)
        {
            try
            {
                this->GetPlayerManager().GetPlayer(player).AddScore(value);
            }
            catch (std::exception&)
            {
            }
        }

        std::list<PlayerEntity*> const& Game::GetListOfPlayers() const
        {
            return this->_players;
        }

        void Game::RegisterPlayerEntity(PlayerEntity* player)
        {
            if (this->_running)
                this->_players.push_back(player);
        }

        void Game::UnregisterPlayerEntity(PlayerEntity* player)
        {
            if (this->_running)
                this->_players.remove(player);
        }

        size_t Game::GetNumberOfPlayers() const
        {
            return this->_players.size();
        }

        MainGame* Game::GetMainGame() const
        {
            return this->_mainGame;
        }

        uint16_t Game::GetCreatorId() const
        {
            return this->_creatorId;
        }

        int Game::GetMode() const
        {
            return this->_mode;
        }

        void Game::SetMainGame(MainGame* mainGame)
        {
            this->_mainGame = mainGame;
        }

        void Game::SetResources(std::map<int, AResourceInfo*> const& resources)
        {
            this->GetResourceManager().CopyResources(resources);
        }

        void Game::SpawnEntities()
        {
            // La room
            delete this->_room;
            this->_room = 0;

            this->StartMap();

            // Le timer
            if (this->_mode == MainGame::ENDURANCE)
                this->_timer = new TimerEntity(*this);

            // Spawn des joueurs
            size_t nb = 0;
            std::list<PlayerEntity*>::iterator it = this->_players.begin();
            std::list<PlayerEntity*>::iterator itEnd = this->_players.end();
            for (; it != itEnd; ++it)
            {
                ++nb;
                if (nb <= MAX_PLAYERS)
                    (*it)->SpawnShip();
            }

            // Les ptites particules
            this->_particles = new ParticleGeneratorEntity(*this);

            // la Barre
            this->_bar.SetResourceId(this->GetResourceManager().GetResourceId(Resources::BAR));
            this->_bar.SetPositionX(Game::WIDTH / 2);
            this->_bar.SetPositionY(Game::FULLHEIGHT - 8);
            this->_bar.SetPositionZ(220);
            this->GetItemManager().AddItem(&this->_bar);

            this->_music.SetResourceId(this->GetResourceManager().GetResourceId(Resources::MUSIC1 + this->R() * 10));
            this->GetItemManager().AddItem(&this->_music);
        }

        void Game::_PreRun(void)
        {
            if (this->_mode == MainGame::ENDURANCE)
                this->SpawnEntities();
            else
                this->_room = new RoomEntity(*this);
        }

        void Game::_PostRun(void)
        {
            delete this->_room;
            delete this->_map;
            delete this->_bg;
            delete this->_particles;
            delete this->_timer;
            this->_mainGame->GameStop(this);
        }

        void Game::_OnRemovePlayer(uint16_t)
        {
            if (this->GetPlayerManager().GetNumberOfPlayers() == 0)
                this->Stop();
        }

        void Game::RegisterShipEntity(ShipEntity* ship)
        {
            if (this->_running)
                this->_playerShips.push_back(ship);
        }

        void Game::UnregisterShipEntity(ShipEntity* ship)
        {
            if (this->_running)
                if (!this->_playerShips.empty())
                    this->_playerShips.remove(ship);
        }

        std::list<ShipEntity*> const& Game::GetListOfPlayerShips() const
        {
            return this->_playerShips;
        }

        std::list<MonsterEntity*> const& Game::GetListOfMonsters() const
        {
            return this->_monsters;
        }

        void Game::RegisterMonsterEntity(MonsterEntity* monster)
        {
            if (this->_running)
                this->_monsters.push_back(monster);
        }

        void Game::UnregisterMonsterEntity(MonsterEntity* monster)
        {
            if (this->_running)
                this->_monsters.remove(monster);
        }

        void Game::RegisterForce(ForceEntity* force)
        {
            if (this->_running)
                this->_forces.push_back(force);
        }

        void Game::UnregisterForce(ForceEntity* force)
        {
            if (this->_running)
                this->_forces.remove(force);
        }

        std::list<ForceEntity*> const& Game::GetForces(void) const
        {
            return this->_forces;
        }

        void Game::RegisterBgTile(BgTileEntity* bg)
        {
            if (this->_running)
                this->_bgTiles.push_back(bg);
        }

        void Game::UnregisterBgTile(BgTileEntity* bg)
        {
            if (this->_running)
                this->_bgTiles.remove(bg);
        }

        void Game::StopBgTiles(void)
        {
            for (std::list<BgTileEntity*>::iterator it = this->_bgTiles.begin(),
                 ite = this->_bgTiles.end() ; it != ite ; ++it)
                (*it)->Stop();
        }

        void Game::StartBgTiles(void)
        {
            for (std::list<BgTileEntity*>::iterator it = this->_bgTiles.begin(),
                 ite = this->_bgTiles.end() ; it != ite ; ++it)
                (*it)->Go();
        }

        void Game::DeleteBgTiles(void)
        {
            for (std::list<BgTileEntity*>::iterator it = this->_bgTiles.begin(),
                 ite = this->_bgTiles.end() ; it != ite ; ++it)
                delete *it;
            this->_bgTiles.clear();
        }

        void Game::RegisterWall(WallEntity* wall)
        {
            if (this->_running)
                this->_walls.push_back(wall);
        }

        void Game::UnregisterWall(WallEntity* wall)
        {
            if (this->_running)
                this->_walls.remove(wall);
        }

        void Game::StopWalls(void)
        {
            for (std::list<WallEntity*>::iterator it = this->_walls.begin(),
                 ite = this->_walls.end() ; it != ite ; ++it)
                (*it)->Stop();
        }

        void Game::StartWalls(void)
        {
            for (std::list<WallEntity*>::iterator it = this->_walls.begin(),
                 ite = this->_walls.end() ; it != ite ; ++it)
                (*it)->Go();
        }

        void Game::StopMap(void)
        {
            delete this->_map;
            this->_map = 0;
            ++this->_mapCounter;
            delete this->_bg;
            this->_bg = 0;
            if (this->_timer != 0)
                this->_timer->Stop();
        }

        void Game::StartMap(void)
        {
            if (this->_mode == MainGame::ENDURANCE)
                this->_map = new EnduranceMap1Entity(*this, this->_enduranceLevel++);
            else if (this->_mapCounter == 0)
                this->_map = new FileMapEntity(*this, "games/rtype/data/maps/level1.txt");
            else
                this->_map = new FileMapEntity(*this, "games/rtype/data/maps/level2.txt");

            int id = Resources::BG1_116x256;
            int width = 116;
            int yOffset = -8;
            if (this->_mode == MainGame::ENDURANCE)
            {
                float r = this->R();
                if (r > 0.66)
                {
                    id = Resources::BG2_102x256;
                    width = 102;
                }
                else if (r > 0.33)
                {
                    id = Resources::BG3_64x256;
                    width = 64;
                }
            }
            else if (this->_mapCounter == 0)
            {
                id = Resources::BG3_64x256;
                width = 64;
            }
            else
            {
                id = Resources::BG2_102x256;
                width = 102;
            }
            this->_bg = new BackgroundEntity(*this, this->GetResourceManager().GetResourceId(id), width, this->_mapCounter == 0 ? true : false, yOffset);

            if (this->_timer != 0)
                this->_timer->Continue();
        }

        int Game::GetNbLives(uint16_t playerId)
        {
            if (this->_lives.find(playerId) != this->_lives.end())
                return this->_lives[playerId];
            this->SetNbLives(playerId, 3);
            return 3;
        }

        void Game::SetNbLives(uint16_t playerId, int nbLives)
        {
            this->_lives[playerId] = nbLives;
        }

        void Game::ChangeMusic(int musicId)
        {
            this->_music.SetResourceId(this->GetResourceManager().GetResourceId(musicId));
        }

        void Game::ChangeMusic(void)
        {
            this->_music.SetResourceId(this->GetResourceManager().GetResourceId(Resources::MUSIC1 + this->R() * 10));
        }

    }
}
