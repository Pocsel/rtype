#include "RoomEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        RoomEntity::RoomEntity(Game& game) :
            GameEntity(game, "Room"), _lastPlayerCount(0)
        {
            this->_start.SetPlayerId(this->_game.GetCreatorId());
            this->_start.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::GAME_START));
            this->_start.SetPositionX(310);
            this->_start.SetPositionY(180);
            this->_game.GetItemManager().AddItem(&this->_start);
            this->_listBg.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::PLAYER_LIST));
            this->_listBg.SetPositionX(120);
            this->_listBg.SetPositionY(120);
            this->_game.GetItemManager().AddItem(&this->_listBg);
        }

        RoomEntity::~RoomEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_listBg);
            this->_game.GetItemManager().RemoveItem(&this->_start);
            this->_ClearList();
        }

        void RoomEntity::_RefreshList()
        {
            this->_ClearList();
            std::list<uint16_t> list = this->_game.GetPlayerManager().GetPlayerIdList();
            float curY = 32;
            std::list<uint16_t>::iterator it = list.begin();
            std::list<uint16_t>::iterator itEnd = list.end();
            for (; it != itEnd; ++it)
            {
                try
                {
                    GamePlayer& p = this->_game.GetPlayerManager().GetPlayer(*it);
                    TextEntity<GameEntity, Game>* txt = new TextEntity<GameEntity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7);
                    txt->SetText(p.GetNick());
                    txt->SetPosition(108, curY);
                    this->_players.push_back(txt);
                    curY += 20;
                }
                catch (std::exception&)
                {
                }
            }
        }

        void RoomEntity::_ClearList()
        {
            std::list<TextEntity<GameEntity, Game>*>::iterator it = this->_players.begin();
            std::list<TextEntity<GameEntity, Game>*>::iterator itEnd = this->_players.end();
            for (; it != itEnd; ++it)
                delete *it;
            this->_players.clear();
        }

        void RoomEntity::Run(float)
        {
            if (this->_lastPlayerCount != this->_game.GetNumberOfPlayers())
            {
                this->_RefreshList();
                this->_lastPlayerCount = this->_game.GetNumberOfPlayers();
            }
            try
            {
                if (this->_game.GetPlayerManager().GetPlayer(this->_game.GetCreatorId()).KeyClicked(Key::Return))
                    this->_game.SpawnEntities();
            }
            catch (std::exception&)
            {
            }
        }

    }
}

