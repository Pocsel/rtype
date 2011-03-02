#include "Game.hpp"
#include "MonsterEntity.hpp"
#include "Resources.hpp"
#include "MonsterInteraction.hpp"
#include "EnemyBulletEntity.hpp"
#include "EnemyDamageInteraction.hpp"
#include "ShipInteraction.hpp"
#include "WallInteraction.hpp"
#include "Decorator.hpp"

namespace Gmgp
{
    namespace Server
    {

        MonsterEntity::MonsterEntity(Game& game,
                                     int spriteId,
                                     int explosionId,
                                     float y,
                                     float speedX,
                                     float w,
                                     float h,
                                     int life,
                                     int score)
            : GameEntity(game, "Monster"),
            _sprite(game.GetElapsedTime()),
            _interaction(new MonsterInteraction(life, this)),
            _width(w),
            _height(h),
            _explosionId(explosionId),
            _score(score)
        {
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(spriteId));
            if (speedX > 0)
                this->_sprite.SetPositionX(-w);
            else
                this->_sprite.SetPositionX(Game::WIDTH + w);
            this->_sprite.SetPositionY(y);
            this->_sprite.SetSpeedX(speedX);
            this->_game.GetItemManager().AddItem(&this->_sprite);

            this->_game.RegisterMonsterEntity(this);
        }

        MonsterEntity::~MonsterEntity()
        {
            this->_game.UnregisterMonsterEntity(this);
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
            this->_game.Score(reinterpret_cast<MonsterInteraction*>(this->_interaction.Get())->GetLastHit(), this->_score);
        }

        void MonsterEntity::GenerateInteractions(float)
        {
            if (reinterpret_cast<MonsterInteraction*>(this->_interaction.Get())->GetLife() <= 0)
                return;
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_interaction,
                                                                                  Rect(this->_sprite.GetPositionX() - this->_width * 0.5f,
                                                                                       this->_sprite.GetPositionY() - this->_height * 0.5f,
                                                                                       this->_width, this->_height));
        }

        void MonsterEntity::Run(float time)
        {
            if (this->_sprite.GetPositionX() < -this->_width - 1 || this->_sprite.GetPositionX() > Game::WIDTH + this->_width + 1)
            {
                delete this;
                return;
            }
            if (reinterpret_cast<MonsterInteraction*>(this->_interaction.Get())->GetLife() <= 0)
            {
                Decorator::Explosion(this->_explosionId, *this);
                delete this;
                return;
            }
            this->_Run(time);
            this->_game.GetEntityManager().GetInteractionManager().Interact(*this,
                                                                            Rect(this->_sprite.GetPositionX() - this->_width * 0.5f,
                                                                                 this->_sprite.GetPositionY() - this->_height * 0.5f,
                                                                                 this->_width, this->_height));
        }

        void MonsterEntity::_Run(float)
        {
        }

        bool MonsterEntity::_Damage(int damage, uint16_t playerId)
        {
            reinterpret_cast<MonsterInteraction*>(this->_interaction.Get())->Damage(damage, playerId);
            if (reinterpret_cast<MonsterInteraction*>(this->_interaction.Get())->GetLife() <= 0 || damage < 0)
            {
                Decorator::PlaySound(this->_game, Resources::ENEMY_DIES1 + this->_game.R() * 4);
                Decorator::Explosion(this->_explosionId, *this);
                delete this;
                return false;
            }
            return true;
        }

        bool MonsterEntity::Interact(FriendlyDamageInteraction& interaction)
        {
            return this->_Damage(interaction.GetValue(), interaction.GetPlayerId());
        }

        bool MonsterEntity::Interact(ShipInteraction& interaction)
        {
            return this->_Damage(500, interaction.GetPlayerId());
        }

        bool MonsterEntity::Interact(WallInteraction&)
        {
            return this->_Damage(-1, 0);
        }

        Point MonsterEntity::GetPosition(void) const
        {
            return Point(this->_sprite.GetPositionX(), this->_sprite.GetPositionY());
        }
    }
}

