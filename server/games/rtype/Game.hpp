#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "Clock.hpp"
#include "GameEntity.hpp"
#include "MonsterGeneratorEntity.hpp"
#include "WallGeneratorEntity.hpp"
#include "BackgroundEntity.hpp"
#include "ParticleGeneratorEntity.hpp"
#include "GamePlayer.hpp"
#include "BasicGame.hpp"
#include "MapEntity.hpp"
#include "RoomEntity.hpp"
#include "TimerEntity.hpp"

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
            explicit Game(uint16_t playerId, int mode);
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

            void RegisterShipEntity(ShipEntity* ship);
            void UnregisterShipEntity(ShipEntity* ship);
            std::list<ShipEntity*> const& GetListOfPlayerShips() const;

            void RegisterMonsterEntity(MonsterEntity* monster);
            void UnregisterMonsterEntity(MonsterEntity* monster);
            std::list<MonsterEntity*> const& GetListOfMonsters() const;

            void RegisterForce(ForceEntity* wall);
            void UnregisterForce(ForceEntity* wall);
            std::list<ForceEntity*> const& GetForces(void) const;

            void RegisterBgTile(BgTileEntity* bg);
            void UnregisterBgTile(BgTileEntity* bg);
            void StopBgTiles(void);
            void StartBgTiles(void);
            void DeleteBgTiles(void);

            void RegisterWall(WallEntity* wall);
            void UnregisterWall(WallEntity* wall);
            void StopWalls(void);
            void StartWalls(void);

            void StopMap(void);
            void StartMap(void);

            int GetNbLives(uint16_t playerId);
            void SetNbLives(uint16_t playerId, int nbLives);

            void ChangeMusic(int musicId);
            void ChangeMusic(void);

        protected:
            virtual void _PreRun(void);
            virtual void _PostRun(void);

            virtual void _OnRemovePlayer(uint16_t playedId);

        private:
            MainGame* _mainGame;
            uint16_t _creatorId;
            MapEntity* _map;
            BackgroundEntity* _bg;
            int _mode;
            RoomEntity* _room;
            std::list<PlayerEntity*> _players;
            std::list<ShipEntity*> _playerShips;
            std::list<MonsterEntity*> _monsters;
            ParticleGeneratorEntity* _particles;
            std::list<BgTileEntity*> _bgTiles;
            std::list<WallEntity*> _walls;
            std::list<ForceEntity*> _forces;
            std::map<uint16_t, int> _lives;
            size_t _enduranceLevel;
            Item _bar;
            TimerEntity* _timer;
            size_t _mapCounter;
            Item _music;
        };

    }
}

#endif

