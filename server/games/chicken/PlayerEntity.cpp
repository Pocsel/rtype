#include "PlayerEntity.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "PlayerManager.hpp"
#include "ItemManager.hpp"
#include "EntityManager.hpp"
#include "Log.hpp"
#include "Constants.hpp"
#include "IGame.hpp"

namespace Gmgp
{
    namespace Server
    {

        PlayerEntity::PlayerEntity(Game& game, uint16_t id) :
            Entity(game, "Player", id), _visor(game.GetElapsedTime()),
            _damage(new DamageInteraction(100, id, this)),
            _bigDamage(new DamageInteraction(1000, id, this))
        {
            this->_visor.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::AIM1));
            this->_visor.SetCursor(true);
            this->_visor.SetPositionZ(200);
            this->_visor.SetPlayerId(id);
            this->_game.GetItemManager().AddItem(&this->_visor);
        }

        PlayerEntity::~PlayerEntity(void)
        {
            this->_game.GetItemManager().RemoveItem(&this->_visor);
        }

        void PlayerEntity::Run(float time)
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

                if (this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId()).ButtonClicked(Mouse::Left))
                {
                    Item i(time);
                    i.SetPositionX(this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId()).GetMouseX());
                    i.SetPositionY(this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId()).GetMouseY());
                    i.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::IMPACT1));
                    i.SetLifeTimeMs(10000);
                    i.SetPositionZ(50);
                    this->_game.GetItemManager().SendItem(i);

                    this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_damage,
                                                                                          Circle(i.GetPositionX(), i.GetPositionY(), 20));

                    Item shootSound;
                    shootSound.SetResourceId(this->_game.GetResourceManager().GetResourceId(Game::SOUND_WEAPON));
                    shootSound.SetLifeTimeCycles(1);
                    this->_game.GetItemManager().SendItem(shootSound);

                }
            }
            catch (std::exception& e)
            {
                Log::W("Player entity: " + String(e.what()));
            }
        }

        void PlayerEntity::PutBigDamage(float posX, float posY)
        {
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_bigDamage, Circle(posX, posY, 100));
        }

    }
}

