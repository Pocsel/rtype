#ifndef __MAINGAME_HPP__
#define __MAINGAME_HPP__

#include "Clock.hpp"
#include "Thread.hpp"
#include "BasicGame.hpp"
#include "Mutex.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Game;
        class MenuEntity;
        class MenuPlayer;

        class MainGame : public BasicGame<MenuEntity, MenuPlayer>
        {
        private:
            struct GameMetadata
            {
                Game* game;
                IThread* thread;
                uint16_t creatorId;
                String name;
                bool running;
            };
        public:
            explicit MainGame(void);
            ~MainGame(void);

            //called from a subgame
            void GameStop(Game* game);

            //called from this game
            void CreateGame(uint16_t playerId);
            void JoinGame(uint16_t playerId, uint16_t targetId);

            size_t GetNumberOfGames();
            std::map<uint16_t, String> GetGameList();

        protected:
            virtual void _InitializeResources(void);

            virtual void _PostRun(void);

        private:
            void _RefreshGames(void);

            std::list<GameMetadata*> _games;
            void _Load(int id, AResourceInfo* res);
            mutable Mutex _mutex;
        };

    }
}

#endif

