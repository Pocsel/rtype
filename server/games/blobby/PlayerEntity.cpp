
#include "PlayerEntity.hpp"
#include "Player.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        PlayerEntity::PlayerEntity(Game& game, uint16_t playerId, String const& nick)
            : Common2PlayerEntity<Entity, Game, PlayerEntity>(game, playerId, nick),
            _player(0)
        {
        }

        PlayerEntity::~PlayerEntity()
        {
            this->Die();
        }

        void PlayerEntity::Run(float)
        {
            try
            {
                Player& player = this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId());
                if (player.KeyClicked(Key::Escape))
                {
                    std::map<uint16_t, IGame*> const& gameList = this->_game.GetServer().GetGameList();
                    IGame* mainGame = gameList.begin()->second;
                    if (mainGame != &this->_game)
                    {
                        Log::D("Player returning to MainMenu.");
                        this->_game.MovePlayer(this->GetPlayerId(), mainGame);
                        return;
                    }
                }

                if (this->_player)
                    this->_DoStuff(player);

            }
            catch (std::exception&)
            {
            }
        }

        void PlayerEntity::_DoStuff(Player& player)
        {
            //TODO
        }

        void PlayerEntity::Spawn(bool p1)
        {
            this->_p1 = p1;
            this->Die();
            this->_player = new Item(this->_game.GetElapsedTime());
            this->_player->SetResourceId(p1 ?
                                         this->_game.GetResourceManager().GetResourceId(Resources::PLAYER1) :
                                         this->_game.GetResourceManager().GetResourceId(Resources::PLAYER2));
            this->_player->SetPositionX(p1 ? (Game::FULLWIDTH / 4) : (Game::FULLWIDTH * 3 / 4));
            this->_player->SetPositionY(Game::FULLHEIGHT - HEIGHT / 2);
            this->_game.GetItemManager().AddItem(this->_player);
        }

        void PlayerEntity::Die()
        {
            if (this->_player)
            {
                this->_game.GetItemManager().RemoveItem(this->_player);
                delete this->_player;
                this->_player = 0;
            }
        }

        bool PlayerEntity::IsAlive()
        {
            return this->_player != 0;
        }

    }
}

