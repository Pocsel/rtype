#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Clock.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "BasicGame.hpp"
#include "ManagerEntity.hpp"
#include "BombEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game : public BasicGame<Entity, Player>
        {
            public:
                enum Constant
                {
                    FULLWIDTH = 640,
                    FULLHEIGHT = 480,
                    TICKS_TIME = 50,
                    X_OFFSET = 8,
                    Y_OFFSET = 48,
                    CASE_SIZE = 16,
                    X_SIZE = 39,
                    Y_SIZE = 27,
                };

            public:
                explicit Game();
                ~Game();
                void RegisterPlayerEntity(PlayerEntity* player);
                void UnregisterPlayerEntity(PlayerEntity* player);
                size_t GetNumberOfPlayers() const;
                std::list<PlayerEntity*> const& GetListOfPlayers() const;
                void RegisterBombEntity(BombEntity* bomb);
                void UnregisterBombEntity(BombEntity* bomb);
                size_t GetNumberOfBombs() const;
                std::list<BombEntity*> const& GetListOfBombs() const;
                bool HasWall(float x, float y) const;
                void SetWall(float x, float y, bool val);
                static int XToCase(float x);
                static int YToCase(float y);
                static float CaseToX(int caseX);
                static float CaseToY(int caseY);

            protected:
                void _InitializeResources();
                virtual void _PreRun();
                virtual void _PostRun();

            private:
                void _Load(int id, AResourceInfo* res);
                std::list<PlayerEntity*> _players;
                std::list<BombEntity*> _bombs;
                ManagerEntity* _manager;
                bool _map[X_SIZE][Y_SIZE];
        };

    }
}

#endif

