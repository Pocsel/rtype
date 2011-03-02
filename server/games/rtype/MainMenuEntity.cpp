#include "MainGame.hpp"
#include "MainMenuEntity.hpp"
#include "PlayerManager.hpp"
#include "Resources.hpp"
#include "Game.hpp"
#include "Decorator.hpp"

namespace Gmgp
{
    namespace Server
    {

        MainMenuEntity::MainMenuEntity(MainGame& game, uint16_t playerId) :
            MenuEntity(game, "MainMenu", playerId), _nbGames(0), _mode(MainGame::NORMAL)
        {
            this->_createGame = new ButtonEntity(this->_game, this->GetPlayerId());
            this->_createGame->SetPosition(250, 207);
            this->_createGame->SetText("Create Game");
            this->_modeButton = new ButtonEntity(this->_game, this->GetPlayerId());
            this->_modeButton->SetPosition(250, 187);
            this->_modeButton->SetText("Mode: Normal");
            this->_background.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::MENU_BACKGROUND));
            this->_background.SetPositionX(Game::WIDTH / 2);
            this->_background.SetPositionY(Game::HEIGHT / 2);
            this->_background.SetPositionZ(0);
            this->_background.SetPlayerId(this->GetPlayerId());
            this->_game.GetItemManager().AddItem(&this->_background);
        }

        MainMenuEntity::~MainMenuEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_background);
            delete this->_createGame;
            delete this->_modeButton;
            this->_RemoveGameList();
        }

        //        void MainMenuEntity::_DisablePlayer()
        //        {
        //            this->_game.GetItemManager().SendDeletionForItemsOfPlayer(this->GetPlayerId());
        //            this->_game.GetItemManager().RemoveAllItemsOfPlayer(this->GetPlayerId());
        //            try
        //            {
        //                this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId()).DisableItems(true);
        //            }
        //            catch (std::exception&)
        //            {
        //            }
        //        }

        void MainMenuEntity::_RemoveGameList()
        {
            std::map<uint16_t, ButtonEntity*>::iterator it = this->_list.begin();
            std::map<uint16_t, ButtonEntity*>::iterator itEnd = this->_list.end();
            for (; it != itEnd; ++it)
                delete it->second;
            this->_list.clear();
        }

        void MainMenuEntity::_UpdateGameList()
        {
            float cur = 115;
            this->_RemoveGameList();
            std::map<uint16_t, String> games = this->_game.GetGameList();
            std::map<uint16_t, String>::iterator it = games.begin();
            std::map<uint16_t, String>::iterator itEnd = games.end();
            for (; it != itEnd; ++it)
            {
                ButtonEntity* e = new ButtonEntity(this->_game, this->GetPlayerId());
                e->SetText(it->second);
                e->SetPosition(50, cur);
                cur += 20;
                this->_list[it->first] = e;
            }
        }

        void MainMenuEntity::Run(float)
        {
            try
            {
                if (this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId()).KeyClicked(Key::Escape))
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

                if (this->_createGame->Clicked())
                {
                    Decorator::PlaySound(this->_game, Resources::MENU_CLIK, this->GetPlayerId());
                    this->_game.CreateGame(this->GetPlayerId(), this->_mode);
                    return;
                }

                if (this->_modeButton->Clicked())
                {
                    Decorator::PlaySound(this->_game, Resources::MENU_CLIK, this->GetPlayerId());
                    if (this->_mode == MainGame::NORMAL)
                    {
                        this->_mode = MainGame::ENDURANCE;
                        this->_modeButton->SetText("Mode: Endurance");
                    }
                    else
                    {
                        this->_mode = MainGame::NORMAL;
                        this->_modeButton->SetText("Mode: Normal");
                    }
                }

                if (this->_nbGames != this->_game.GetNumberOfGames()) // pas terrible comme condition
                {
                    this->_UpdateGameList();
                    this->_nbGames = this->_game.GetNumberOfGames();
                }

                std::map<uint16_t, ButtonEntity*>::iterator it = this->_list.begin();
                std::map<uint16_t, ButtonEntity*>::iterator itEnd = this->_list.end();
                for (; it != itEnd; ++it)
                {
                    if (it->second->Clicked())
                    {
                        Decorator::PlaySound(this->_game, Resources::MENU_CLIK, this->GetPlayerId());
                        this->_game.JoinGame(this->GetPlayerId(), it->first);
                        return;
                    }
                }
            }
            catch (std::exception&)
            {
            }
        }

    }
}
