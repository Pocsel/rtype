#include "MainGame.hpp"
#include "AnimationResourceInfo.hpp"
#include "SoundResourceInfo.hpp"
#include "LuaResourceInfo.hpp"
#include "functor.hpp"
#include "Resources.hpp"
#include "Game.hpp"
#include "MenuEntity.hpp"
#include "MenuPlayer.hpp"
#include "ScopeLock.hpp"

namespace Gmgp
{
    namespace Server
    {

        MainGame::MainGame(void)
            : BasicGame<MenuEntity, MenuPlayer>("Bust-A-Move", 40, 384, 256)
        {
            Log::I("Bust-A-Move Menu created.");
        }

        MainGame::~MainGame(void)
        {
            Log::I("Bust-A-Move Menu destroyed.");
        }

        void MainGame::_PostRun(void)
        {
            // Stop
            {
                ScopeLock lock(this->_mutex);
                for (std::list<GameMetadata*>::iterator it = this->_games.begin(),
                     ite = this->_games.end() ; it != ite ; ++it)
                    (*it)->game->Stop();
            }

            // erase !!
            {
                usleep(1000);
                this->_mutex.Lock();
                while (this->_games.size())
                {
                    this->_RefreshGames();
                    this->_mutex.UnLock();
                    usleep(1000);
                    this->_mutex.Lock();
                }
                this->_mutex.UnLock();
            }
        }

        void MainGame::GameStop(Game* game)
        {
            ScopeLock lock(this->_mutex);
            for (std::list<GameMetadata*>::iterator it = this->_games.begin(), ite = this->_games.end() ;
                 it != ite ; ++it)
            {
                if ((*it)->game == game)
                {
                    (*it)->running = false;
                    return;
                }
            }
        }

        void MainGame::_RefreshGames(void)
        {
            std::list<GameMetadata*> toDel;
            for (std::list<GameMetadata*>::iterator it = this->_games.begin(), ite = this->_games.end() ;
                 it != ite ; ++it)
            {
                if ((*it)->running == false)
                    toDel.push_back(*it);
            }

            for (std::list<GameMetadata*>::iterator it = toDel.begin(), ite = toDel.end() ; it != ite ; ++it)
            {
                (*it)->thread->Join();
                delete (*it)->thread;
                delete (*it)->game;
                delete *it;
                this->_games.remove(*it);
            }
        }

        void MainGame::JoinGame(uint16_t playerId, uint16_t targetId)
        {
            ScopeLock lock(this->_mutex);
            if (!this->GetPlayerManager().HasPlayer(playerId))
                return;
            std::list<GameMetadata*>::const_iterator it = this->_games.begin();
            std::list<GameMetadata*>::const_iterator itEnd = this->_games.end();
            for (; it != itEnd; ++it)
                if ((*it)->creatorId == targetId)
                {
                    MenuPlayer& p = this->GetPlayerManager().GetPlayer(playerId);
                    this->MovePlayer(p.GetId(), (*it)->game);
                    return;
                }
        }

        size_t MainGame::GetNumberOfGames()
        {
            ScopeLock lock(this->_mutex);
            this->_RefreshGames();
            return this->_games.size();
        }

        std::map<uint16_t, String> MainGame::GetGameList()
        {
            ScopeLock lock(this->_mutex);
            this->_RefreshGames();
            std::map<uint16_t, String> ret;
            std::list<GameMetadata*>::const_iterator it = this->_games.begin();
            std::list<GameMetadata*>::const_iterator itEnd = this->_games.end();
            for (; it != itEnd; ++it)
                ret[(*it)->creatorId] = (*it)->name;
            return ret;
        }

        void MainGame::CreateGame(uint16_t playerId)
        {
            ScopeLock lock(this->_mutex);
            if (!this->GetPlayerManager().HasPlayer(playerId))
                return;
            MenuPlayer& p = this->GetPlayerManager().GetPlayer(playerId);
            Game* game = new Game(p.GetId());
            if (!game->Initialize(this->GetServer()))
            {
                delete game;
                return;
            }
            game->SetMainGame(this);
            game->SetResources(this->GetResourceManager().GetResources());
            GameMetadata* meta = new GameMetadata;
            meta->game = game;
            meta->creatorId = playerId;
            meta->name = p.GetNick() + "\'s Game";
            meta->thread = new Thread(b00st::bind(&IGame::Run, static_cast<IGame&>(*game)));
            meta->running = true;
            this->_games.push_back(meta);
            this->MovePlayer(p.GetId(), game);
        }

        void MainGame::_Load(int id, AResourceInfo* res)
        {
            this->GetResourceManager().RegisterResource(id, res);
        }

        void MainGame::_InitializeResources(void)
        {
            this->_Load(Resources::FONT, new AnimationResourceInfo("common/data/animations/font1.png", 94, 0, false));
//            this->_Load(Resources::WALL2_DOWN_128x48_1, new AnimationResourceInfo("rtype/data/animations/wall2-down-128x48-1.png", 1, 0, false));
//
//            this->_Load(Resources::LUA_PARTICLE, new LuaResourceInfo("rtype/data/lua/particle.lua", "rtypeParticle"));
//
//            this->_Load(Resources::MUSIC, new SoundResourceInfo("rtype/data/sounds/[FF7-0] A great Sucess.ogg", true));
//
//            this->_Load(Resources::BIG_BULLET_FIRE, new SoundResourceInfo("rtype/data/sounds/big_bullet_fire.wav", false));
        }

    }
}

