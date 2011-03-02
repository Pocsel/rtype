
#include "FlameEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "FriendlyDamageInteraction.hpp"
#include "WallInteraction.hpp"
#include "Decorator.hpp"


namespace Gmgp
{
    namespace Server
    {

        FlameEntity::FlameEntity(Game& game, bool up, float posX, float posY, uint16_t playerId /* = 0*/)
            : FriendlyBulletEntity(game, InteractionPtr(new FriendlyDamageInteraction(40, playerId, this)),
                                   Resources::FLAME_THROWER_BULLET, Resources::FLAME_THROWER_EXPLOSION,
                                   posX, posY,
                                   0,
                                   (up ? -SPEED : SPEED),
                                   7, 9, playerId),
            _up(up),
            _boingCount(0)
            {
                this->SetDamage(100);
            }

        FlameEntity::~FlameEntity(void)
        {
        }

        bool FlameEntity::Interact(WallInteraction& interaction)
        {
            if (++this->_boingCount > MAX_BOING)
            {
                delete this;
                return false;
            }
            Point const& ipos = interaction.GetPosition();
            Point const& isize = interaction.GetSize();
            Circle testArea(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 8);
            if (testArea.Intersect(Rect(ipos.x - isize.x * 0.5f, ipos.y + isize.y * 0.5f, isize.x, 1)))
            {// barre en BAS
                this->_up = true;
                this->_sprite.SetPositionX(testArea.position.x);
                this->_sprite.SetPositionY(ipos.y + isize.y * 0.5f + 7.5f);
                this->_sprite.SetSpeedX(SPEED);
                this->_sprite.SetSpeedY(0);
            }
            else if (testArea.Intersect(Rect(ipos.x - isize.x * 0.5f, ipos.y - isize.y * 0.5f, isize.x, 1)))
            {// barre en HAUT
                this->_up = false;
                this->_sprite.SetPositionX(testArea.position.x);
                this->_sprite.SetPositionY(ipos.y - isize.y * 0.5f - 7.5f);
                this->_sprite.SetSpeedX(SPEED);
                this->_sprite.SetSpeedY(0);
            }
            else
            {// barre a GAUCHE ou a DROITE
                if (this->_up)
                {
                    this->_up = false;
                    this->_sprite.SetPositionX(ipos.x - isize.x * 0.5f - 7.5f);
                    this->_sprite.SetPositionY(testArea.position.y);
                    this->_sprite.SetSpeedX(-Game::WALL_SPEED);
                    this->_sprite.SetSpeedY(SPEED);
                }
                else
                {
                    this->_up = true;
                    this->_sprite.SetPositionX(ipos.x - isize.x * 0.5f - 7.5f);
                    this->_sprite.SetPositionY(testArea.position.y);
                    this->_sprite.SetSpeedX(-Game::WALL_SPEED);
                    this->_sprite.SetSpeedY(-SPEED);
                }
            }
            return true;
        }

        void FlameEntity::_ExplodeEffects(void)
        {
            Decorator::PlaySound(this->_game, Resources::FLAME);
        }

    }
}


