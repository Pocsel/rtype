#include "Game.hpp"
#include "PlayerManager.hpp"
#include "AnimationResourceInfo.hpp"
#include "SoundResourceInfo.hpp"
#include "Resources.hpp"
#include "MainGame.hpp"

namespace Gmgp
{
    namespace Server
    {

        Game::Game(uint16_t playerId)
            : BasicGame<GameEntity, GamePlayer>("Bust-A-Move Game", Game::TICKS_TIME, Game::FULLWIDTH, Game::FULLHEIGHT),
            _mainGame(0),
            _creatorId(playerId),
            _room(0)
        {
            Log::I("Bust-A-Move Game created.");
        }

        Game::~Game(void)
        {
            Log::I("Bust-A-Move Game destroyed.");
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

//            this->StartMap();
//
//            // Spawn des joueurs
//            size_t nb = 0;
//            std::list<PlayerEntity*>::iterator it = this->_players.begin();
//            std::list<PlayerEntity*>::iterator itEnd = this->_players.end();
//            for (; it != itEnd; ++it)
//            {
//                ++nb;
//                if (nb <= MAX_PLAYERS)
//                    (*it)->SpawnShip();
//            }

//            this->_music.SetResourceId(this->GetResourceManager().GetResourceId(Resources::MUSIC1 + this->R() * 10));
//            this->GetItemManager().AddItem(&this->_music);
        }

        void Game::_PreRun(void)
        {
            this->_room = new RoomEntity(*this);
        }

        void Game::_PostRun(void)
        {
            delete this->_room;
            this->_mainGame->GameStop(this);
        }

        void Game::_OnRemovePlayer(uint16_t)
        {
            if (this->GetPlayerManager().GetNumberOfPlayers() == 0)
                this->Stop();
        }

        void Game::ChangeMusic(int musicId)
        {
            this->_music.SetResourceId(this->GetResourceManager().GetResourceId(musicId));
        }

        void Game::ChangeMusic(void)
        {
//            this->_music.SetResourceId(this->GetResourceManager().GetResourceId(Resources::MUSIC1 + this->R() * 10));
        }

    }
}
