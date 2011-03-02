#include "Game.hpp"
#include "MenuEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        MenuEntity::MenuEntity(Game& game, uint16_t playerId, String const& nick) :
            Entity(game, "Menu", playerId)
        {
            this->_text = new TextEntity<Entity, Game>(game, this->_game.GetResourceManager().GetResourceId(Game::FONT), 7, playerId);
            this->_text->SetText("Welcome " + nick + "! Choose a game:");
            this->_text->SetPosition(20, 20);

            std::map<uint16_t, IGame*> const& gameList = this->_game.GetServer().GetGameList();
            this->_gameList = &gameList;
            float curY = 50;
            std::map<uint16_t, IGame*>::const_iterator it = gameList.begin();
            std::map<uint16_t, IGame*>::const_iterator itEnd = gameList.end();
            for (; it != itEnd; ++it)
            {
                if (it == gameList.begin()) // la premiere game est MainMenu, on la prend pas
                    continue;
                ButtonEntity* b = new ButtonEntity(this->_game, this->GetPlayerId());
                b->SetText(it->second->GetName());
                b->SetPosition(60, curY);
                this->_buttons[it->first] = b;
                curY += 20;
            }

            this->_bg.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::BG));
            this->_bg.SetPlayerId(playerId);
            this->_bg.SetPositionX(320 / 2);
            this->_bg.SetPositionY(240 / 2);
            this->_bg.SetPositionZ(0);
            this->_game.GetItemManager().AddItem(&this->_bg);

            this->_cursor.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::CURSOR));
            this->_cursor.SetPlayerId(playerId);
            this->_cursor.SetCursor(true);
            this->_cursor.SetPositionZ(250);
            this->_game.GetItemManager().AddItem(&this->_cursor);
        }

        MenuEntity::~MenuEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_bg);
            this->_game.GetItemManager().RemoveItem(&this->_cursor);
            std::map<uint16_t, ButtonEntity*>::iterator it = this->_buttons.begin();
            std::map<uint16_t, ButtonEntity*>::iterator itEnd = this->_buttons.end();
            for (; it != itEnd; ++it)
                delete it->second;
            delete this->_text;
        }

        void MenuEntity::Run(float)
        {
            std::map<uint16_t, ButtonEntity*>::iterator it = this->_buttons.begin();
            std::map<uint16_t, ButtonEntity*>::iterator itEnd = this->_buttons.end();
            for (; it != itEnd; ++it)
                if (it->second->Clicked())
                {
                    Log::D("Player chose game " + String(it->first) + ".");
                    this->_game.MovePlayer(this->GetPlayerId(), this->_gameList->find(it->first)->second);
                    return;
                }
        }

    }
}

