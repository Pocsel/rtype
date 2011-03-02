
#include "ExplosiveEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "FriendlyDamageInteraction.hpp"
#include "WallInteraction.hpp"
#include "Decorator.hpp"

namespace Gmgp
{
    namespace Server
    {

        ExplosiveEntity::ExplosiveEntity(Game& game, bool forward, float posX, float posY, uint16_t playerId /* = 0*/)
            : FriendlyBulletEntity(game, InteractionPtr(new FriendlyDamageInteraction(400, playerId, this)),
                                   (forward ? Resources::CONCUSSION_MISSILE : Resources::CONCUSSION_MISSILE_REVERSE),
                                   Resources::EXPLOSION6, posX, posY,
                                   (forward ? SPEED : -SPEED),
                                   0,
                                   2, 45, playerId),
            _deathTime(game.GetElapsedTime() + TIME)
        {
        }

        ExplosiveEntity::~ExplosiveEntity(void)
        {
        }

        void ExplosiveEntity::Run(float time)
        {
            if (time > this->_deathTime)
            {
                this->_Explode(true);
                delete this;
                return;
            }

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

        bool ExplosiveEntity::Interact(WallInteraction&)
        {
            this->_Explode(true);
            delete this;
            return false;
        }

        void ExplosiveEntity::_ExplodeEffects(void)
        {
            Decorator::PlaySound(this->_game, Resources::EXPLOSIVE);
        }


    }
}

