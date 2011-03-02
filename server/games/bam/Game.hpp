#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Clock.hpp"
#include "GameEntity.hpp"
#include "GamePlayer.hpp"
#include "BasicGame.hpp"
#include "RoomEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        class MainGame;
        class BgTileEntity;
        class WallEntity;
        class ForceEntity;

        class Game : public BasicGame<GameEntity, GamePlayer>
        {
        public:
            enum Constant
            {
                FULLWIDTH = 384,
                FULLHEIGHT = 256,
                WIDTH = 384,
                HEIGHT = 240,
                WALL_SPEED = 20,
                BG_SPEED = 15,
                MAX_PLAYERS = 4,
                TICKS_TIME = 20
            };

        public:
            explicit Game(uint16_t playerId);
            ~Game(void);
            void SetResources(std::map<int, AResourceInfo*> const& resources);
            void SetMainGame(MainGame* mainGame);
            MainGame* GetMainGame() const;
            int GetMode() const;
            void SpawnEntities();
            uint16_t GetCreatorId() const;
            void RegisterPlayerEntity(PlayerEntity* player);
            void UnregisterPlayerEntity(PlayerEntity* player);
            size_t GetNumberOfPlayers() const;
            std::list<PlayerEntity*> const& GetListOfPlayers() const;
            void Score(uint16_t playerId, size_t value);

            void ChangeMusic(int musicId);
            void ChangeMusic(void);

        protected:
            virtual void _PreRun(void);
            virtual void _PostRun(void);

            virtual void _OnRemovePlayer(uint16_t playedId);

        private:
            MainGame* _mainGame;
            uint16_t _creatorId;
            RoomEntity* _room;
            std::list<PlayerEntity*> _players;
            Item _music;
        };

    }
}

#endif

