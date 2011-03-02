#include "PlayerEntity.hpp"
#include "MainGame.hpp"
#include "Game.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {

        PlayerEntity::PlayerEntity(Game& game, uint16_t playerId, String const& nick) :
            GameEntity(game, "Player", playerId)
        {
            this->_game.RegisterPlayerEntity(this);
        }

        PlayerEntity::~PlayerEntity()
        {
//            this->_DestroyScoreboard();
            this->_game.UnregisterPlayerEntity(this);
        }

//        void PlayerEntity::_CreateScoreboard()
//        {
//            this->_scoreboardOpen = true;
//            this->_scoreboard.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::SCORE));
//            this->_scoreboard.SetPositionX(Game::WIDTH / 2);
//            this->_scoreboard.SetPositionY(Game::HEIGHT / 2);
//            this->_scoreboard.SetPositionZ(250);
//            this->_scoreboard.SetPlayerId(this->GetPlayerId());
//            this->_game.GetItemManager().AddItem(&this->_scoreboard);
//            std::list<PlayerEntity*> const& list = this->_game.GetListOfPlayers();
//            float curY = 72;
//            std::list<PlayerEntity*>::const_iterator it = list.begin();
//            std::list<PlayerEntity*>::const_iterator itEnd = list.end();
//            for (; it != itEnd; ++it)
//            {
//                if (!(*it)->HasShip())
//                    continue;
//                try
//                {
//                    GamePlayer& p = this->_game.GetPlayerManager().GetPlayer((*it)->GetPlayerId());
//                    TextEntity<GameEntity, Game>* txt = new TextEntity<GameEntity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7, this->GetPlayerId());
//                    txt->SetText(p.GetNick());
//                    txt->SetPosition(90, curY, 251);
//                    this->_nicks.push_back(txt);
//                    TextEntity<GameEntity, Game>* s = new TextEntity<GameEntity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7, this->GetPlayerId());
//                    this->_scores.push_back(std::pair<uint16_t, TextEntity<GameEntity, Game>*>(p.GetId(), s));
//                    curY += 20;
//                }
//                catch (std::exception&)
//                {
//                }
//            }
//        }

//        void PlayerEntity::_DestroyScoreboard()
//        {
//            if (!this->_scoreboardOpen)
//                return;
//            this->_scoreboardOpen = false;
//            this->_game.GetItemManager().RemoveItem(&this->_scoreboard);
//            std::list<TextEntity<GameEntity, Game>*>::iterator it = this->_nicks.begin();
//            std::list<TextEntity<GameEntity, Game>*>::iterator itEnd = this->_nicks.end();
//            for (; it != itEnd; ++it)
//                delete *it;
//            this->_nicks.clear();
//            std::list< std::pair<uint16_t, TextEntity<GameEntity, Game>*> >::iterator it2 = this->_scores.begin();
//            std::list< std::pair<uint16_t, TextEntity<GameEntity, Game>*> >::iterator itEnd2 = this->_scores.end();
//            for (; it2 != itEnd2; ++it2)
//                delete it2->second;
//            this->_scores.clear();
//        }

//        void PlayerEntity::_UpdateScoreboard()
//        {
//            if (!this->_scoreboardOpen)
//                return;
//            float curY = 72;
//            std::list< std::pair<uint16_t, TextEntity<GameEntity, Game>*> >::iterator it = this->_scores.begin();
//            std::list< std::pair<uint16_t, TextEntity<GameEntity, Game>*> >::iterator itEnd = this->_scores.end();
//            for (; it != itEnd; ++it)
//            {
//                try
//                {
//                    GamePlayer& p = this->_game.GetPlayerManager().GetPlayer(it->first);
//                    String score = p.GetScore();
//                    if (it->second->GetText() != score)
//                    {
//                        it->second->SetText(score);
//                        it->second->SetPosition(200, curY, 251);
//                    }
//                }
//                catch (std::exception&)
//                {
//                }
//                curY += 20;
//            }
//        }

        void PlayerEntity::Run(float)
        {
            try
            {
                GamePlayer& p = this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId());
                if (p.KeyClicked(Key::Escape))
                {
                    this->_game.MovePlayer(this->GetPlayerId(), this->_game.GetMainGame());
                    return;
                }
                if (p.KeyClicked(Key::Tab))
                {
//                    if (this->_scoreboardOpen)
//                        this->_DestroyScoreboard();
//                    else
//                        this->_CreateScoreboard();
                }
//                this->_UpdateScoreboard();
            }
            catch (std::exception&)
            {
            }
        }

    }
}

