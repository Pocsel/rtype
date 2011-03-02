#include "MainGame.hpp"
#include "AnimationResourceInfo.hpp"
#include "SoundResourceInfo.hpp"
#include "LuaResourceInfo.hpp"
#include "functor.hpp"
#include "Resources.hpp"
#include "Game.hpp"

namespace Gmgp
{
    namespace Server
    {

        MainGame::MainGame(void)
            : BasicGame<MenuEntity, MenuPlayer>("R-Type", 40, 384, 256)
        {
            Log::I("R-Type Menu created.");
        }

        MainGame::~MainGame(void)
        {
            Log::I("R-Type Menu destroyed.");
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

        void MainGame::CreateGame(uint16_t playerId, int mode)
        {
            ScopeLock lock(this->_mutex);
            if (!this->GetPlayerManager().HasPlayer(playerId))
                return;
            MenuPlayer& p = this->GetPlayerManager().GetPlayer(playerId);
            Game* game = new Game(p.GetId(), mode);
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
            meta->name = p.GetNick() + " " + (mode == MainGame::ENDURANCE ? "(endurance)" : "(normal)");
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
            this->_Load(Resources::CURSOR, new AnimationResourceInfo("rtype/data/animations/cursor.png", 1, 0, false));
            this->_Load(Resources::MENU_BACKGROUND, new AnimationResourceInfo("rtype/data/animations/background_trype.png", 1, 0, false));
            this->_Load(Resources::POULET_GLAMOUR, new AnimationResourceInfo("rtype/data/animations/poulet-glamour.jpg", 1, 0, false));
            this->_Load(Resources::PLAYER_LIST, new AnimationResourceInfo("rtype/data/animations/player-list.png", 1, 0, false));
            this->_Load(Resources::GAME_START, new AnimationResourceInfo("rtype/data/animations/game-start.png", 1, 0, false));
            this->_Load(Resources::SCORE, new AnimationResourceInfo("rtype/data/animations/score.png", 1, 0, false));
            this->_Load(Resources::BAR, new AnimationResourceInfo("rtype/data/animations/bar.png", 1, 0, false));
            this->_Load(Resources::LIVES, new AnimationResourceInfo("rtype/data/animations/lives.png", 4, 0, true));

            this->_Load(Resources::BGFADE_600x240, new AnimationResourceInfo("rtype/data/animations/bgfade.png", 1, 0, false));
            this->_Load(Resources::BG1_116x256, new AnimationResourceInfo("rtype/data/animations/bg1.png", 1, 0, false));
            this->_Load(Resources::BG2_102x256, new AnimationResourceInfo("rtype/data/animations/bg2.png", 1, 0, false));
            this->_Load(Resources::BG3_64x256, new AnimationResourceInfo("rtype/data/animations/bg3.png", 1, 0, false));

            this->_Load(Resources::BOSS_LIFE, new AnimationResourceInfo("rtype/data/animations/boss-life.png", 100, 0, true));
            this->_Load(Resources::POWER_CADRE, new AnimationResourceInfo("rtype/data/animations/power-cadre.png", 1, 0, false));
            this->_Load(Resources::POWER_EMPTY, new AnimationResourceInfo("rtype/data/animations/power-empty.png", 1, 0, false));
            this->_Load(Resources::POWER_LOADING, new AnimationResourceInfo("rtype/data/animations/power-loading.png", 100, 20, true));
            this->_Load(Resources::POWER_FULL, new AnimationResourceInfo("rtype/data/animations/power-full.png", 10, 30, true));
            this->_Load(Resources::POWER_FULL_EFFECT, new AnimationResourceInfo("rtype/data/animations/power-full-effect.png", 5, 80, false));

            this->_Load(Resources::MISSILE_LAUNCHER_LEFT, new AnimationResourceInfo("rtype/data/animations/missile-launcher-left.png", 6, 200, false));
            this->_Load(Resources::MISSILE_LAUNCHER_UP, new AnimationResourceInfo("rtype/data/animations/missile-launcher-up.png", 2, 0, false));
            this->_Load(Resources::ROTATING_MISSILE, new AnimationResourceInfo("rtype/data/animations/rotating-missile.png", 8, 25, false));
            this->_Load(Resources::ROTATING_MISSILE_FIXED, new AnimationResourceInfo("rtype/data/animations/rotating-missile.png", 8, 0, false));
            this->_Load(Resources::MISSILE_UP, new AnimationResourceInfo("rtype/data/animations/missile-up.png", 1, 0, false));
            this->_Load(Resources::MISSILE_CENTER, new AnimationResourceInfo("rtype/data/animations/missile-center.png", 1, 0, false));
            this->_Load(Resources::MISSILE_DOWN, new AnimationResourceInfo("rtype/data/animations/missile-down.png", 1, 0, false));
            this->_Load(Resources::MISSILE_FIRE, new AnimationResourceInfo("rtype/data/animations/missile-fire.png", 2, 50, false));
            this->_Load(Resources::SMOKE, new AnimationResourceInfo("rtype/data/animations/smoke.png", 8, 170, false));

            this->_Load(Resources::SHIP1, new AnimationResourceInfo("rtype/data/animations/ship1.png", 5, 0, false));
            this->_Load(Resources::SHIP2, new AnimationResourceInfo("rtype/data/animations/ship2.png", 5, 0, false));
            this->_Load(Resources::SHIP3, new AnimationResourceInfo("rtype/data/animations/ship3.png", 5, 0, false));
            this->_Load(Resources::SHIP4, new AnimationResourceInfo("rtype/data/animations/ship4.png", 5, 0, false));
            this->_Load(Resources::SHIP5, new AnimationResourceInfo("rtype/data/animations/ship5.png", 5, 0, false));

            this->_Load(Resources::BONUS_CARRIER, new AnimationResourceInfo("rtype/data/animations/bonus-carrier.png", 1, 0, false));
            this->_Load(Resources::BONUS_SPEED, new AnimationResourceInfo("rtype/data/animations/bonus-speed.png", 1, 0, false));
            this->_Load(Resources::BONUS_FORCE, new AnimationResourceInfo("rtype/data/animations/bonus-force.png", 1, 0, false));
            this->_Load(Resources::BONUS_FORCE_BOING_LASER, new AnimationResourceInfo("rtype/data/animations/bonus-force-boing-laser.png", 1, 0, false));
            this->_Load(Resources::BONUS_FORCE_DNA_STYLE, new AnimationResourceInfo("rtype/data/animations/bonus-force-dna-style.png", 1, 0, false));
            this->_Load(Resources::BONUS_FORCE_EXPLOSIVE, new AnimationResourceInfo("rtype/data/animations/bonus-force-explosive.png", 1, 0, false));
            this->_Load(Resources::BONUS_FORCE_FLAME_THROWER, new AnimationResourceInfo("rtype/data/animations/bonus-force-flame-thrower.png", 1, 0, false));

            this->_Load(Resources::FORCE1_20x16, new AnimationResourceInfo("rtype/data/animations/force1.png", 5, 120, false));
            this->_Load(Resources::FORCE2_27x22, new AnimationResourceInfo("rtype/data/animations/force2.png", 6, 120, false));
            this->_Load(Resources::FORCE3_ATTACHED_31x28, new AnimationResourceInfo("rtype/data/animations/force3-attached.png", 4, 120, false));
            this->_Load(Resources::FORCE3_DEPLOYED_29x32, new AnimationResourceInfo("rtype/data/animations/force3-deployed.png", 4, 120, false));
            this->_Load(Resources::FORCE3_LAUNCHED_32x24, new AnimationResourceInfo("rtype/data/animations/force3-launched.png", 4, 120, false));

            this->_Load(Resources::FORCE_BULLET_RIGHT, new AnimationResourceInfo("rtype/data/animations/force-bullet-right.png", 1, 0, false));
            this->_Load(Resources::FORCE_BULLET_LEFT, new AnimationResourceInfo("rtype/data/animations/force-bullet-left.png", 1, 0, false));
            this->_Load(Resources::FORCE_BULLET_UP, new AnimationResourceInfo("rtype/data/animations/force-bullet-up.png", 1, 0, false));
            this->_Load(Resources::FORCE_BULLET_UP_EXPLOSION, new AnimationResourceInfo("rtype/data/animations/force-bullet-up-explosion.png", 2, 84, true));
            this->_Load(Resources::FORCE_BULLET_UPRIGHT, new AnimationResourceInfo("rtype/data/animations/force-bullet-upright.png", 1, 0, false));
            this->_Load(Resources::FORCE_BULLET_UPRIGHT_EXPLOSION, new AnimationResourceInfo("rtype/data/animations/force-bullet-upright-explosion.png", 2, 84, false));
            this->_Load(Resources::FORCE_BULLET_UPLEFT, new AnimationResourceInfo("rtype/data/animations/force-bullet-upleft.png", 1, 0, false));
            this->_Load(Resources::FORCE_BULLET_UPLEFT_EXPLOSION, new AnimationResourceInfo("rtype/data/animations/force-bullet-upleft-explosion.png", 2, 84, false));
            this->_Load(Resources::FORCE_BULLET_DOWN, new AnimationResourceInfo("rtype/data/animations/force-bullet-down.png", 1, 0, false));
            this->_Load(Resources::FORCE_BULLET_DOWN_EXPLOSION, new AnimationResourceInfo("rtype/data/animations/force-bullet-down-explosion.png", 2, 84, true));
            this->_Load(Resources::FORCE_BULLET_DOWNRIGHT, new AnimationResourceInfo("rtype/data/animations/force-bullet-downright.png", 1, 0, false));
            this->_Load(Resources::FORCE_BULLET_DOWNRIGHT_EXPLOSION, new AnimationResourceInfo("rtype/data/animations/force-bullet-downright-explosion.png", 2, 84, false));
            this->_Load(Resources::FORCE_BULLET_DOWNLEFT, new AnimationResourceInfo("rtype/data/animations/force-bullet-downleft.png", 1, 0, false));
            this->_Load(Resources::FORCE_BULLET_DOWNLEFT_EXPLOSION, new AnimationResourceInfo("rtype/data/animations/force-bullet-downleft-explosion.png", 2, 84, false));

            this->_Load(Resources::DNA_STYLE_BULLET, new AnimationResourceInfo("rtype/data/animations/dna-style-bullet.png", 8, 25, true));
            this->_Load(Resources::DNA_STYLE_BULLET_REVERSE, new AnimationResourceInfo("rtype/data/animations/dna-style-bullet-reverse.png", 8, 25, true));
            this->_Load(Resources::DNA_STYLE_EXPLOSION, new AnimationResourceInfo("rtype/data/animations/dna-style-explosion.png", 8, 34, false));
            this->_Load(Resources::BOING_LASER_BULLET, new AnimationResourceInfo("rtype/data/animations/boing-laser-bullet.png", 7, 0, false));
            this->_Load(Resources::BOING_LASER_EXPLOSION, new AnimationResourceInfo("rtype/data/animations/boing-laser-explosion.png", 4, 84, false));
            this->_Load(Resources::FLAME_THROWER_BULLET, new AnimationResourceInfo("rtype/data/animations/flame-thrower-bullet.png", 4, 60, false));
            this->_Load(Resources::FLAME_THROWER_EXPLOSION, new AnimationResourceInfo("rtype/data/animations/flame-thrower-explosion.png", 4, 60, false));
            this->_Load(Resources::CONCUSSION_MISSILE, new AnimationResourceInfo("rtype/data/animations/concussion-missile.png", 2, 50, true));
            this->_Load(Resources::CONCUSSION_MISSILE_REVERSE, new AnimationResourceInfo("rtype/data/animations/concussion-missile-reverse.png", 2, 50, true));
            this->_Load(Resources::HGRENADE, new AnimationResourceInfo("rtype/data/animations/hgrenade.png", 32, 22, true));

            this->_Load(Resources::BULLET1, new AnimationResourceInfo("rtype/data/animations/bullet1.png", 1, 0, false));
            this->_Load(Resources::BULLET2, new AnimationResourceInfo("rtype/data/animations/bullet2.png", 4, 45, false));
            this->_Load(Resources::BULLET3, new AnimationResourceInfo("rtype/data/animations/bullet3.png", 1, 0, false));
            this->_Load(Resources::BULLET4, new AnimationResourceInfo("rtype/data/animations/bullet4.png", 2, 60, false));
            this->_Load(Resources::BULLET5, new AnimationResourceInfo("rtype/data/animations/bullet5.png", 2, 60, false));
            this->_Load(Resources::BULLET6, new AnimationResourceInfo("rtype/data/animations/bullet6.png", 2, 60, false));
            this->_Load(Resources::BULLET7, new AnimationResourceInfo("rtype/data/animations/bullet7.png", 2, 60, true));

            this->_Load(Resources::EXPLOSION1, new AnimationResourceInfo("rtype/data/animations/explosion1.png", 2, 84, false));
            this->_Load(Resources::EXPLOSION1_REVERSE, new AnimationResourceInfo("rtype/data/animations/explosion1-reverse.png", 2, 84, false));
            this->_Load(Resources::EXPLOSION2, new AnimationResourceInfo("rtype/data/animations/explosion2.png", 6, 45, false));
            this->_Load(Resources::EXPLOSION3, new AnimationResourceInfo("rtype/data/animations/explosion3.png", 5, 64, false));
            this->_Load(Resources::EXPLOSION4, new AnimationResourceInfo("rtype/data/animations/explosion4.png", 11, 57, false));
            this->_Load(Resources::EXPLOSION5, new AnimationResourceInfo("rtype/data/animations/explosion5.png", 8, 31, false));
            this->_Load(Resources::EXPLOSION6, new AnimationResourceInfo("rtype/data/animations/explosion6.png", 28, 31, false));
            this->_Load(Resources::EXPLOSION7, new AnimationResourceInfo("rtype/data/animations/explosion7.png", 6, 90, false));
            this->_Load(Resources::EXPLOSION8, new AnimationResourceInfo("rtype/data/animations/explosion8.png", 10, 90, false));
            this->_Load(Resources::EXPLOSION9, new AnimationResourceInfo("rtype/data/animations/bigexplosion999.png", 19, 73, false));

            this->_Load(Resources::MONSTER1, new AnimationResourceInfo("rtype/data/animations/monster1.png", 8, 110, false));
            this->_Load(Resources::MONSTER2, new AnimationResourceInfo("rtype/data/animations/monster2.png", 4, 220, false));
            this->_Load(Resources::MONSTER2_REVERSE, new AnimationResourceInfo("rtype/data/animations/monster2-reverse.png", 4, 220, false));

            this->_Load(Resources::GARBAGE_SPAWNER_UP, new AnimationResourceInfo("rtype/data/animations/garbage-spawner-up.png", 4, 0, false));
            this->_Load(Resources::GARBAGE_SPAWNER_DOWN, new AnimationResourceInfo("rtype/data/animations/garbage-spawner-down.png", 4, 0, false));
            this->_Load(Resources::GARBAGE1, new AnimationResourceInfo("rtype/data/animations/garbage1.png", 1, 0, false));
            this->_Load(Resources::GARBAGE2, new AnimationResourceInfo("rtype/data/animations/garbage2.png", 1, 0, false));
            this->_Load(Resources::GARBAGE3, new AnimationResourceInfo("rtype/data/animations/garbage3.png", 1, 0, false));
            this->_Load(Resources::GARBAGE4, new AnimationResourceInfo("rtype/data/animations/garbage4.png", 1, 0, false));
            this->_Load(Resources::GARBAGE5, new AnimationResourceInfo("rtype/data/animations/garbage5.png", 1, 0, false));

            this->_Load(Resources::BOSS1_BODY, new AnimationResourceInfo("rtype/data/animations/boss1-body.png", 1, 0, false));
            this->_Load(Resources::BOSS1_BULLET, new AnimationResourceInfo("rtype/data/animations/boss1-bullet.png", 4, 120, false));
            this->_Load(Resources::BOSS1_NODE, new AnimationResourceInfo("rtype/data/animations/boss1-node.png", 1, 0, false));
            this->_Load(Resources::BOSS1_QUEUE, new AnimationResourceInfo("rtype/data/animations/boss1-queue.png", 16, 200, false));
            this->_Load(Resources::BOSS1_TENIA_CLOSE, new AnimationResourceInfo("rtype/data/animations/boss1-tenia-close.png", 6, 200, true));
            this->_Load(Resources::BOSS1_TENIA_CLOSED, new AnimationResourceInfo("rtype/data/animations/boss1-tenia-closed.png", 1, 0, true));
            this->_Load(Resources::BOSS1_TENIA_LOOP, new AnimationResourceInfo("rtype/data/animations/boss1-tenia-loop.png", 4, 130, true));
            this->_Load(Resources::BOSS1_TENIA_OPEN, new AnimationResourceInfo("rtype/data/animations/boss1-tenia-open.png", 6, 200, true));

            this->_Load(Resources::WALL1_UP_64x16_1, new AnimationResourceInfo("rtype/data/animations/wall1-up-64x16-1.png", 1, 0, false));
            this->_Load(Resources::WALL1_UP_64x16_2, new AnimationResourceInfo("rtype/data/animations/wall1-up-64x16-2.png", 1, 0, false));
            this->_Load(Resources::WALL1_UP_64x16_3, new AnimationResourceInfo("rtype/data/animations/wall1-up-64x16-3.png", 1, 0, false));
            this->_Load(Resources::WALL1_UP_64x48_1, new AnimationResourceInfo("rtype/data/animations/wall1-up-64x48-1.png", 1, 0, false));
            this->_Load(Resources::WALL1_DOWN_64x16_1, new AnimationResourceInfo("rtype/data/animations/wall1-down-64x16-1.png", 1, 0, false));
            this->_Load(Resources::WALL1_DOWN_64x16_2, new AnimationResourceInfo("rtype/data/animations/wall1-down-64x16-2.png", 1, 0, false));
            this->_Load(Resources::WALL1_DOWN_64x16_3, new AnimationResourceInfo("rtype/data/animations/wall1-down-64x16-3.png", 1, 0, false));
            this->_Load(Resources::WALL1_DOWN_64x48_1, new AnimationResourceInfo("rtype/data/animations/wall1-down-64x48-1.png", 1, 0, false));

            this->_Load(Resources::WALL2_UP_64x16_1, new AnimationResourceInfo("rtype/data/animations/wall2-up-64x16-1.png", 1, 0, false));
            this->_Load(Resources::WALL2_UP_64x48_1, new AnimationResourceInfo("rtype/data/animations/wall2-up-64x48-1.png", 1, 0, false));
            this->_Load(Resources::WALL2_UP_128x16_1, new AnimationResourceInfo("rtype/data/animations/wall2-up-128x16-1.png", 1, 0, false));
            this->_Load(Resources::WALL2_UP_128x48_1, new AnimationResourceInfo("rtype/data/animations/wall2-up-128x48-1.png", 1, 0, false));
            this->_Load(Resources::WALL2_DOWN_64x16_1, new AnimationResourceInfo("rtype/data/animations/wall2-down-64x16-1.png", 1, 0, false));
            this->_Load(Resources::WALL2_DOWN_64x48_1, new AnimationResourceInfo("rtype/data/animations/wall2-down-64x48-1.png", 1, 0, false));
            this->_Load(Resources::WALL2_DOWN_128x16_1, new AnimationResourceInfo("rtype/data/animations/wall2-down-128x16-1.png", 1, 0, false));
            this->_Load(Resources::WALL2_DOWN_128x48_1, new AnimationResourceInfo("rtype/data/animations/wall2-down-128x48-1.png", 1, 0, false));

            this->_Load(Resources::LUA_PARTICLE, new LuaResourceInfo("rtype/data/lua/particle.lua", "rtypeParticle"));
            this->_Load(Resources::LUA_MISSILE, new LuaResourceInfo("rtype/data/lua/missile.lua", "rtypeMissile"));
            this->_Load(Resources::PARTICLE1, new AnimationResourceInfo("rtype/data/animations/particle1.png", 3, 200, false));

            this->_Load(Resources::MUSIC, new SoundResourceInfo("rtype/data/sounds/[FF7-0] A great Sucess.ogg", true));
            this->_Load(Resources::MUSIC0, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Ambiance Prison 2.ogg", true));
            this->_Load(Resources::MUSIC1, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Ambiance Prison.ogg", true));
            this->_Load(Resources::MUSIC2, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Bifurcation Dangereuse.ogg", true));
            this->_Load(Resources::MUSIC3, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Dark Blood Opening.ogg", true));
            this->_Load(Resources::MUSIC4, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Deep Labyrinth.ogg", true));
            this->_Load(Resources::MUSIC5, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Fighting is my purpose.ogg", true));
            this->_Load(Resources::MUSIC6, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Le Guerrier Silencieux.ogg", true));
            this->_Load(Resources::MUSIC7, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Le Manoir de Nibelheim.ogg", true));
            this->_Load(Resources::MUSIC8, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Manoir Shinra.ogg", true));
            this->_Load(Resources::MUSIC9, new SoundResourceInfo("rtype/data/sounds/[FF7-0] Nightmare.ogg", true));

            this->_Load(Resources::BIG_BULLET_FIRE, new SoundResourceInfo("rtype/data/sounds/big_bullet_fire.wav", false));
            this->_Load(Resources::BONUS1, new SoundResourceInfo("rtype/data/sounds/bonus1.wav", false));
            this->_Load(Resources::BONUS2, new SoundResourceInfo("rtype/data/sounds/bonus2.wav", false));
            this->_Load(Resources::BONUS3, new SoundResourceInfo("rtype/data/sounds/bonus3.wav", false));
            this->_Load(Resources::BOSS_DIES, new SoundResourceInfo("rtype/data/sounds/boss_dies.wav", false));
            this->_Load(Resources::BOSS_FIRES, new SoundResourceInfo("rtype/data/sounds/boss_fires.wav", false));
            this->_Load(Resources::BOSS_READY, new SoundResourceInfo("rtype/data/sounds/boss_ready.wav", false));
            this->_Load(Resources::CHARGED2, new SoundResourceInfo("rtype/data/sounds/charged2.wav", false));
            this->_Load(Resources::CHARGED, new SoundResourceInfo("rtype/data/sounds/charged.wav", false));
            this->_Load(Resources::DNA, new SoundResourceInfo("rtype/data/sounds/dna.wav", false));
            this->_Load(Resources::ENEMY_DIES1, new SoundResourceInfo("rtype/data/sounds/enemy_dies1.wav", false));
            this->_Load(Resources::ENEMY_DIES2, new SoundResourceInfo("rtype/data/sounds/enemy_dies2.wav", false));
            this->_Load(Resources::ENEMY_DIES3, new SoundResourceInfo("rtype/data/sounds/enemy_dies3.wav", false));
            this->_Load(Resources::ENEMY_DIES4, new SoundResourceInfo("rtype/data/sounds/enemy_dies4.wav", false));
            this->_Load(Resources::EXPLOSIVE, new SoundResourceInfo("rtype/data/sounds/explosive.wav", false));
            this->_Load(Resources::FLAME, new SoundResourceInfo("rtype/data/sounds/flame.wav", false));
            this->_Load(Resources::LASER, new SoundResourceInfo("rtype/data/sounds/laser.wav", false));
            this->_Load(Resources::MENU_CLIK, new SoundResourceInfo("rtype/data/sounds/menu_clik.wav", false));
            this->_Load(Resources::PLAYER_DIES, new SoundResourceInfo("rtype/data/sounds/player_dies.wav", false));
            this->_Load(Resources::PLAYER_ONLINE, new SoundResourceInfo("rtype/data/sounds/player_online.wav", false));

        }

    }
}

