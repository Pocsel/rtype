
#include "BulletEntity.hpp"
#include "Game.hpp"
#include "WallInteraction.hpp"
#include "Decorator.hpp"

namespace Gmgp
{
    namespace Server
    {

        BulletEntity::BulletEntity(Game& game,
                                   InteractionPtr const& damage,
                                   int spriteLocalId,
                                   int explosionLocalId,
                                   float posX,
                                   float posY,
                                   float speedX,
                                   float speedY,
                                   float radius,
                                   float explosionRadius,
                                   uint16_t playerId)
            : GameEntity(game, "Bullet", playerId),
            _sprite(game.GetElapsedTime()),
            _explosionLocalId(explosionLocalId),
            _damage(damage),
            _radius(radius),
            _explosionRadius(explosionRadius)
        {
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(spriteLocalId));
            this->_sprite.SetPositionX(posX);
            this->_sprite.SetPositionY(posY);
            this->_sprite.SetSpeedX(speedX);
            this->_sprite.SetSpeedY(speedY);
            this->_sprite.SetPositionZ(120);
            this->_game.GetItemManager().AddItem(&this->_sprite);
        }

        BulletEntity::~BulletEntity(void)
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
        }

        void BulletEntity::Run(float)
        {
            if (this->_sprite.GetPositionX() > Game::WIDTH ||
                this->_sprite.GetPositionX() < 0 ||
                this->_sprite.GetPositionY() > Game::HEIGHT ||
                this->_sprite.GetPositionY() < 0)
            {
                delete this;
                return;
            }
            this->_game.GetEntityManager().GetInteractionManager().Interact(*this,
                                                                            Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), this->_radius));
        }

        void BulletEntity::_Explode(bool damage)
        {
            Decorator::Explosion(this->_explosionLocalId, *this);

            if (damage)
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_damage,
                                                                                      Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), this->_explosionRadius));
        }

        void BulletEntity::_ExplodeEffects(void)
        {
        }

        bool BulletEntity::Interact(WallInteraction&)
        {
            this->_Explode();
            delete this;
            return false;
        }

    }
}
