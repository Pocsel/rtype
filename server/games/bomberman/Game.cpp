#include "Game.hpp"
#include "PlayerManager.hpp"
#include "AnimationResourceInfo.hpp"
#include "SoundResourceInfo.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        Game::Game()
            : BasicGame<Entity, Player>("Bomberman", TICKS_TIME, FULLWIDTH, FULLHEIGHT)
        {
            Log::I("Bomberman game created.");
            for (int y = 0; y < Y_SIZE; ++y)
                for (int x = 0; x < X_SIZE; ++x)
                    if (x == 0 || x == X_SIZE - 1 || y == 0 || y == Y_SIZE - 1)
                        this->_map[x][y] = true;
                    else if (x % 2 != 0 || y % 2 != 0)
                        this->_map[x][y] = false;
                    else
                        this->_map[x][y] = true;
        }

        Game::~Game()
        {
            Log::I("Bomberman game destroyed.");
        }

        void Game::_InitializeResources()
        {
            this->_Load(Resources::COUNTER, new AnimationResourceInfo("bomberman/data/animations/counter.png", 6, 1000, false));
            this->_Load(Resources::FONT, new AnimationResourceInfo("common/data/animations/font1.png", 94, 0, false));
            this->_Load(Resources::BACKGROUND_IG, new AnimationResourceInfo("bomberman/data/animations/background-ig.png", 1, 0, false));
            this->_Load(Resources::BOMB, new AnimationResourceInfo("bomberman/data/animations/bomb.png", 4, 125, false));
            this->_Load(Resources::BONUS_BOMB, new AnimationResourceInfo("bomberman/data/animations/bonus-bomb.png", 6, 30, false));
            this->_Load(Resources::BONUS_DEATH, new AnimationResourceInfo("bomberman/data/animations/bonus-death.png", 6, 30, false));
            this->_Load(Resources::BONUS_MULTI, new AnimationResourceInfo("bomberman/data/animations/bonus-multi.png", 6, 30, false));
            this->_Load(Resources::BONUS_POWER, new AnimationResourceInfo("bomberman/data/animations/bonus-power.png", 6, 30, false));
            this->_Load(Resources::BONUS_PUSH, new AnimationResourceInfo("bomberman/data/animations/bonus-push.png", 6, 30, false));
            this->_Load(Resources::BONUS_THROW, new AnimationResourceInfo("bomberman/data/animations/bonus-throw.png", 6, 30, false));
            this->_Load(Resources::EXPLOSION_CENTER, new AnimationResourceInfo("bomberman/data/animations/explosion-center.png", 4, 120, false));
            this->_Load(Resources::EXPLOSION_DOWN, new AnimationResourceInfo("bomberman/data/animations/explosion-down.png", 4, 120, false));
            this->_Load(Resources::EXPLOSION_HORIZONTAL, new AnimationResourceInfo("bomberman/data/animations/explosion-horizontal.png", 4, 120, false));
            this->_Load(Resources::EXPLOSION_LEFT, new AnimationResourceInfo("bomberman/data/animations/explosion-left.png", 4, 120, false));
            this->_Load(Resources::EXPLOSION_RIGHT, new AnimationResourceInfo("bomberman/data/animations/explosion-right.png", 4, 120, false));
            this->_Load(Resources::EXPLOSION_UP, new AnimationResourceInfo("bomberman/data/animations/explosion-up.png", 4, 120, false));
            this->_Load(Resources::EXPLOSION_VERTICAL, new AnimationResourceInfo("bomberman/data/animations/explosion-vertical.png", 4, 120, false));
            this->_Load(Resources::P1_DEATH, new AnimationResourceInfo("bomberman/data/animations/p1-death.png", 8, 60, false));
            this->_Load(Resources::P2_DEATH, new AnimationResourceInfo("bomberman/data/animations/p2-death.png", 8, 60, false));
            this->_Load(Resources::P3_DEATH, new AnimationResourceInfo("bomberman/data/animations/p3-death.png", 8, 60, false));
            this->_Load(Resources::P4_DEATH, new AnimationResourceInfo("bomberman/data/animations/p4-death.png", 8, 60, false));
            this->_Load(Resources::P5_DEATH, new AnimationResourceInfo("bomberman/data/animations/p5-death.png", 8, 60, false));
            this->_Load(Resources::P6_DEATH, new AnimationResourceInfo("bomberman/data/animations/p6-death.png", 8, 60, false));
            this->_Load(Resources::P7_DEATH, new AnimationResourceInfo("bomberman/data/animations/p7-death.png", 8, 60, false));
            this->_Load(Resources::P8_DEATH, new AnimationResourceInfo("bomberman/data/animations/p8-death.png", 8, 60, false));
            this->_Load(Resources::P1_DOWN_IMMO, new AnimationResourceInfo("bomberman/data/animations/p1-down-immo.png", 1, 0, false));
            this->_Load(Resources::P2_DOWN_IMMO, new AnimationResourceInfo("bomberman/data/animations/p2-down-immo.png", 1, 0, false));
            this->_Load(Resources::P3_DOWN_IMMO, new AnimationResourceInfo("bomberman/data/animations/p3-down-immo.png", 1, 0, false));
            this->_Load(Resources::P4_DOWN_IMMO, new AnimationResourceInfo("bomberman/data/animations/p4-down-immo.png", 1, 0, false));
            this->_Load(Resources::P5_DOWN_IMMO, new AnimationResourceInfo("bomberman/data/animations/p5-down-immo.png", 1, 0, false));
            this->_Load(Resources::P6_DOWN_IMMO, new AnimationResourceInfo("bomberman/data/animations/p6-down-immo.png", 1, 0, false));
            this->_Load(Resources::P7_DOWN_IMMO, new AnimationResourceInfo("bomberman/data/animations/p7-down-immo.png", 1, 0, false));
            this->_Load(Resources::P8_DOWN_IMMO, new AnimationResourceInfo("bomberman/data/animations/p8-down-immo.png", 1, 0, false));
            this->_Load(Resources::P1_DOWN_MOVE, new AnimationResourceInfo("bomberman/data/animations/p1-down-move.png", 4, 60, false));
            this->_Load(Resources::P2_DOWN_MOVE, new AnimationResourceInfo("bomberman/data/animations/p2-down-move.png", 4, 60, false));
            this->_Load(Resources::P3_DOWN_MOVE, new AnimationResourceInfo("bomberman/data/animations/p3-down-move.png", 4, 60, false));
            this->_Load(Resources::P4_DOWN_MOVE, new AnimationResourceInfo("bomberman/data/animations/p4-down-move.png", 4, 60, false));
            this->_Load(Resources::P5_DOWN_MOVE, new AnimationResourceInfo("bomberman/data/animations/p5-down-move.png", 4, 60, false));
            this->_Load(Resources::P6_DOWN_MOVE, new AnimationResourceInfo("bomberman/data/animations/p6-down-move.png", 4, 60, false));
            this->_Load(Resources::P7_DOWN_MOVE, new AnimationResourceInfo("bomberman/data/animations/p7-down-move.png", 4, 60, false));
            this->_Load(Resources::P8_DOWN_MOVE, new AnimationResourceInfo("bomberman/data/animations/p8-down-move.png", 4, 60, false));
            this->_Load(Resources::P1_ICON, new AnimationResourceInfo("bomberman/data/animations/p1-icon.png", 1, 0, false));
            this->_Load(Resources::P2_ICON, new AnimationResourceInfo("bomberman/data/animations/p2-icon.png", 1, 0, false));
            this->_Load(Resources::P3_ICON, new AnimationResourceInfo("bomberman/data/animations/p3-icon.png", 1, 0, false));
            this->_Load(Resources::P4_ICON, new AnimationResourceInfo("bomberman/data/animations/p4-icon.png", 1, 0, false));
            this->_Load(Resources::P5_ICON, new AnimationResourceInfo("bomberman/data/animations/p5-icon.png", 1, 0, false));
            this->_Load(Resources::P6_ICON, new AnimationResourceInfo("bomberman/data/animations/p6-icon.png", 1, 0, false));
            this->_Load(Resources::P7_ICON, new AnimationResourceInfo("bomberman/data/animations/p7-icon.png", 1, 0, false));
            this->_Load(Resources::P8_ICON, new AnimationResourceInfo("bomberman/data/animations/p8-icon.png", 1, 0, false));
            this->_Load(Resources::P1_LEFT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p1-left-immo.png", 1, 0, false));
            this->_Load(Resources::P2_LEFT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p2-left-immo.png", 1, 0, false));
            this->_Load(Resources::P3_LEFT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p3-left-immo.png", 1, 0, false));
            this->_Load(Resources::P4_LEFT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p4-left-immo.png", 1, 0, false));
            this->_Load(Resources::P5_LEFT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p5-left-immo.png", 1, 0, false));
            this->_Load(Resources::P6_LEFT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p6-left-immo.png", 1, 0, false));
            this->_Load(Resources::P7_LEFT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p7-left-immo.png", 1, 0, false));
            this->_Load(Resources::P8_LEFT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p8-left-immo.png", 1, 0, false));
            this->_Load(Resources::P1_LEFT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p1-left-move.png", 4, 60, false));
            this->_Load(Resources::P2_LEFT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p2-left-move.png", 4, 60, false));
            this->_Load(Resources::P3_LEFT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p3-left-move.png", 4, 60, false));
            this->_Load(Resources::P4_LEFT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p4-left-move.png", 4, 60, false));
            this->_Load(Resources::P5_LEFT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p5-left-move.png", 4, 60, false));
            this->_Load(Resources::P6_LEFT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p6-left-move.png", 4, 60, false));
            this->_Load(Resources::P7_LEFT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p7-left-move.png", 4, 60, false));
            this->_Load(Resources::P8_LEFT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p8-left-move.png", 4, 60, false));
            this->_Load(Resources::P1_RIGHT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p1-right-immo.png", 1, 0, false));
            this->_Load(Resources::P2_RIGHT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p2-right-immo.png", 1, 0, false));
            this->_Load(Resources::P3_RIGHT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p3-right-immo.png", 1, 0, false));
            this->_Load(Resources::P4_RIGHT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p4-right-immo.png", 1, 0, false));
            this->_Load(Resources::P5_RIGHT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p5-right-immo.png", 1, 0, false));
            this->_Load(Resources::P6_RIGHT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p6-right-immo.png", 1, 0, false));
            this->_Load(Resources::P7_RIGHT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p7-right-immo.png", 1, 0, false));
            this->_Load(Resources::P8_RIGHT_IMMO, new AnimationResourceInfo("bomberman/data/animations/p8-right-immo.png", 1, 0, false));
            this->_Load(Resources::P1_RIGHT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p1-right-move.png", 4, 60, false));
            this->_Load(Resources::P2_RIGHT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p2-right-move.png", 4, 60, false));
            this->_Load(Resources::P3_RIGHT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p3-right-move.png", 4, 60, false));
            this->_Load(Resources::P4_RIGHT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p4-right-move.png", 4, 60, false));
            this->_Load(Resources::P5_RIGHT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p5-right-move.png", 4, 60, false));
            this->_Load(Resources::P6_RIGHT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p6-right-move.png", 4, 60, false));
            this->_Load(Resources::P7_RIGHT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p7-right-move.png", 4, 60, false));
            this->_Load(Resources::P8_RIGHT_MOVE, new AnimationResourceInfo("bomberman/data/animations/p8-right-move.png", 4, 60, false));
            this->_Load(Resources::P1_UP_IMMO, new AnimationResourceInfo("bomberman/data/animations/p1-up-immo.png", 1, 0, false));
            this->_Load(Resources::P2_UP_IMMO, new AnimationResourceInfo("bomberman/data/animations/p2-up-immo.png", 1, 0, false));
            this->_Load(Resources::P3_UP_IMMO, new AnimationResourceInfo("bomberman/data/animations/p3-up-immo.png", 1, 0, false));
            this->_Load(Resources::P4_UP_IMMO, new AnimationResourceInfo("bomberman/data/animations/p4-up-immo.png", 1, 0, false));
            this->_Load(Resources::P5_UP_IMMO, new AnimationResourceInfo("bomberman/data/animations/p5-up-immo.png", 1, 0, false));
            this->_Load(Resources::P6_UP_IMMO, new AnimationResourceInfo("bomberman/data/animations/p6-up-immo.png", 1, 0, false));
            this->_Load(Resources::P7_UP_IMMO, new AnimationResourceInfo("bomberman/data/animations/p7-up-immo.png", 1, 0, false));
            this->_Load(Resources::P8_UP_IMMO, new AnimationResourceInfo("bomberman/data/animations/p8-up-immo.png", 1, 0, false));
            this->_Load(Resources::P1_UP_MOVE, new AnimationResourceInfo("bomberman/data/animations/p1-up-move.png", 4, 60, false));
            this->_Load(Resources::P2_UP_MOVE, new AnimationResourceInfo("bomberman/data/animations/p2-up-move.png", 4, 60, false));
            this->_Load(Resources::P3_UP_MOVE, new AnimationResourceInfo("bomberman/data/animations/p3-up-move.png", 4, 60, false));
            this->_Load(Resources::P4_UP_MOVE, new AnimationResourceInfo("bomberman/data/animations/p4-up-move.png", 4, 60, false));
            this->_Load(Resources::P5_UP_MOVE, new AnimationResourceInfo("bomberman/data/animations/p5-up-move.png", 4, 60, false));
            this->_Load(Resources::P6_UP_MOVE, new AnimationResourceInfo("bomberman/data/animations/p6-up-move.png", 4, 60, false));
            this->_Load(Resources::P7_UP_MOVE, new AnimationResourceInfo("bomberman/data/animations/p7-up-move.png", 4, 60, false));
            this->_Load(Resources::P8_UP_MOVE, new AnimationResourceInfo("bomberman/data/animations/p8-up-move.png", 4, 60, false));
            this->_Load(Resources::WALL_DESTROY, new AnimationResourceInfo("bomberman/data/animations/wall-destroy.png", 6, 100, false));
            this->_Load(Resources::WALL, new AnimationResourceInfo("bomberman/data/animations/wall.png", 1, 0, false));
            this->_Load(Resources::TAUNT, new AnimationResourceInfo("bomberman/data/animations/taunt.png", 3, 80, false));

            this->_Load(Resources::WA_EXPLOSION1, new SoundResourceInfo("bomberman/data/sounds/wa-explosion1.wav", false));
            this->_Load(Resources::WA_EXPLOSION2, new SoundResourceInfo("bomberman/data/sounds/wa-explosion2.wav", false));
            this->_Load(Resources::WA_EXPLOSION3, new SoundResourceInfo("bomberman/data/sounds/wa-explosion3.wav", false));
            this->_Load(Resources::WA_INGAME1, new SoundResourceInfo("bomberman/data/sounds/wa-ingame1.ogg", true));
            this->_Load(Resources::WA_INGAME2, new SoundResourceInfo("bomberman/data/sounds/wa-ingame2.ogg", true));
            this->_Load(Resources::WA_INGAME3, new SoundResourceInfo("bomberman/data/sounds/wa-ingame3.ogg", true));
            this->_Load(Resources::WA_INGAME4, new SoundResourceInfo("bomberman/data/sounds/wa-ingame4.ogg", true));
            this->_Load(Resources::WA_KILL, new SoundResourceInfo("bomberman/data/sounds/wa-kill.wav", false));
            this->_Load(Resources::WA_PUTBOMB, new SoundResourceInfo("bomberman/data/sounds/wa-putbomb.wav", false));
            this->_Load(Resources::WA_WIN, new SoundResourceInfo("bomberman/data/sounds/wa-win.wav", false));
            this->_Load(Resources::AOK_ROGGAN, new SoundResourceInfo("bomberman/data/sounds/aok-roggan.ogg", false));
            this->_Load(Resources::AOK_WOLOLO, new SoundResourceInfo("bomberman/data/sounds/aok-wololo.ogg", false));
        }

        int Game::XToCase(float x)
        {
            return static_cast<int>((x - X_OFFSET) / CASE_SIZE);
        }

        int Game::YToCase(float y)
        {
            return static_cast<int>((y - Y_OFFSET) / CASE_SIZE);
        }

        float Game::CaseToX(int x)
        {
            return static_cast<float>(x * CASE_SIZE + X_OFFSET + CASE_SIZE / 2);
        }

        float Game::CaseToY(int y)
        {
            return static_cast<float>(y * CASE_SIZE + Y_OFFSET + CASE_SIZE / 2);
        }

        bool Game::HasWall(float x, float y) const
        {
            int cx = XToCase(x);
            int cy = YToCase(y);
            if (cx < 0 || cx >= X_SIZE || cy < 0 || cy >= Y_SIZE)
                return false;
            return this->_map[cx][cy];
        }

        void Game::SetWall(float x, float y, bool val)
        {
            int cx = XToCase(x);
            int cy = YToCase(y);
            if (cx < 0 || cx >= X_SIZE || cy < 0 || cy >= Y_SIZE)
                return;
            this->_map[cx][cy] = val;
        }

        void Game::_Load(int id, AResourceInfo* res)
        {
            this->GetResourceManager().RegisterResource(id, res);
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

        std::list<PlayerEntity*> const& Game::GetListOfPlayers() const
        {
            return this->_players;
        }

        void Game::RegisterBombEntity(BombEntity* bomb)
        {
            if (this->_running)
                this->_bombs.push_back(bomb);
        }

        void Game::UnregisterBombEntity(BombEntity* bomb)
        {
            if (this->_running)
                this->_bombs.remove(bomb);
        }

        size_t Game::GetNumberOfBombs() const
        {
            return this->_bombs.size();
        }

        std::list<BombEntity*> const& Game::GetListOfBombs() const
        {
            return this->_bombs;
        }

        void Game::_PreRun()
        {
            this->_manager = new ManagerEntity(*this);
        }

        void Game::_PostRun()
        {
            delete this->_manager;
        }

    }
}
