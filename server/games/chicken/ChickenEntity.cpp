#include "ChickenEntity.hpp"
#include "DamageInteraction.hpp"
#include "Game.hpp"
#include "TextEntity.hpp"
#include "EntityManager.hpp"
#include "ItemManager.hpp"
#include "PlayerManager.hpp"
#include "Log.hpp"

namespace Gmgp
{
    namespace Server
    {

        ChickenEntity::ChickenEntity(Game& game, bool super)
            : Entity(game, "Chicken"), _sprite(game.GetElapsedTime()), _superChicken(false)
        {
            int type = static_cast<int>(this->_game.R() * 4);
            int dir = static_cast<int>(this->_game.R() * 2);

            switch (type)
            {
                case 0:
                this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId((dir ? Game::CHICKEN1_LEFT : Game::CHICKEN1_RIGHT)));
                this->_deathLocalId = Game::CHICKEN1_DEATH;
                break;
                case 1:
                this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId((dir ? Game::CHICKEN2_LEFT : Game::CHICKEN2_RIGHT)));
                this->_deathLocalId = Game::CHICKEN2_DEATH;
                break;
                case 2:
                this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId((dir ? Game::CHICKEN3_LEFT : Game::CHICKEN3_RIGHT)));
                this->_deathLocalId = Game::CHICKEN3_DEATH;
                break;
                case 3:
                case 4:
                this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId((dir ? Game::CHICKEN4_LEFT : Game::CHICKEN4_RIGHT)));
                this->_deathLocalId = Game::CHICKEN4_DEATH;
            }

            this->_sprite.SetPositionX((dir ? 640.0f : 0.0f));
            this->_sprite.SetPositionY(this->_game.R() * 380.0f + 70.0f);
            this->_sprite.SetSpeedX((100.0f + this->_game.R() * 100.0f) * (dir ? -1.0f : 1.0f));
            this->_sprite.SetSpeedY(-10.0f - this->_game.R() * 120.0f);
            this->_sprite.SetAccelY(40.0f - this->_game.R() * 60.0f);

            if (super || this->_game.R() < 0.03)
            {
                this->_superChicken = true;
                this->_sprite.SetBlinking(130);
            }

            this->_game.GetItemManager().AddItem(&this->_sprite);
        }

        ChickenEntity::~ChickenEntity(void)
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
        }

        void ChickenEntity::Run(float)
        {
            if (this->_sprite.GetPositionX() > 650 || this->_sprite.GetPositionX() < -10 ||
                this->_sprite.GetPositionY() > 490 || this->_sprite.GetPositionY() < -10)
            {
                delete this;
                return;
            }
            this->_game.GetEntityManager().GetInteractionManager().Interact(*this, Point(this->_sprite.GetPositionX(), this->_sprite.GetPositionY()));
        }

        bool ChickenEntity::Interact(DamageInteraction& interaction)
        {
            if (interaction.GetValue() > 0)
            {
                this->_Explode(this->_deathLocalId);
                this->_CreateFeathers();
                this->_MakeSound(Game::SOUND_DEATH);
                if (this->_superChicken)
                {
                    this->_Explode(Game::BIG_EXPLOSION);
                    this->_MakeSound(Game::SOUND_EXPLOSION);
                }


                TextEntity* txt = new TextEntity(this->_game, this->_game.GetResourceManager().GetResourceId(Game::FONT), 7);
                txt->EnableAutoRemove(this->_game.GetElapsedTime() + 1.8f);
                txt->SetRemoveStyle(TextEntity::NICE);
                try
                {
                    uint16_t id = interaction.GetPlayerId();
                    this->_game.GetPlayerManager().GetPlayer(id).IncrementScore(1);
                    if (this->_superChicken)
                        this->_game.GetPlayerManager().GetPlayer(id).PutBigDamage(this->_sprite.GetPositionX(), this->_sprite.GetPositionY());
                    txt->SetText(this->_game.GetPlayerManager().GetPlayer(id).GetNick());
                }
                catch (std::exception&)
                {
                    txt->SetText("Unknown");
                }
                txt->SetPosition(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 100);
                txt->SetBlinking(30);
                txt->SetSpeed(0, -30);

                delete this;
                return false;
            }
            return true;
        }

        void ChickenEntity::_Explode(int resourceLocalId)
        {
            Item i;
            i.SetResourceId(this->_game.GetResourceManager().GetResourceId(resourceLocalId));
            i.SetPositionX(this->_sprite.GetPositionX());
            i.SetPositionY(this->_sprite.GetPositionY());
            i.SetLifeTimeCycles(1);
            i.SetPositionZ(130);
            this->_game.GetItemManager().SendItem(i);
        }

        void ChickenEntity::_CreateFeathers(void)
        {
            size_t nbPlumes = static_cast<size_t>(6 + this->_game.R() * 10);
            for (size_t i = 0; i < nbPlumes; ++i)
            {
                Item p;
                Game::LocalResourceId res = this->_game.R() > 0.5 ? Game::CHICKEN_BLOOD1 : Game::CHICKEN_BLOOD2;
                p.SetResourceId(this->_game.GetResourceManager().GetResourceId(res));
                p.SetPositionX(this->_sprite.GetPositionX());
                p.SetPositionY(this->_sprite.GetPositionY());
                p.SetDisapear(true);
                p.SetPositionZ(129);
                p.SetSpeedX(-150 + this->_game.R() * 300);
                p.SetSpeedY(-170 - this->_game.R() * 100);
                p.SetAccelY(300);
                this->_game.GetItemManager().SendItem(p);
            }
        }

        void ChickenEntity::_MakeSound(int resourceLocalId)
        {
                Item deathSound;
                deathSound.SetResourceId(this->_game.GetResourceManager().GetResourceId(resourceLocalId));
                deathSound.SetLifeTimeCycles(1);
                this->_game.GetItemManager().SendItem(deathSound);
        }

    }
}

