
#include "BoingLaserEntity.hpp"
#include "Resources.hpp"
#include "FriendlyDamageInteraction.hpp"
#include "WallInteraction.hpp"
#include "Decorator.hpp"


namespace Gmgp
{
    namespace Server
    {

        BoingLaserEntity::BoingLaserEntity(Game& game, Direction direction, float posX, float posY, uint16_t playerId /* = 0*/)
            : FriendlyBulletEntity(game, InteractionPtr(new FriendlyDamageInteraction(30, playerId, this)),
                                   Resources::BOING_LASER_BULLET, Resources::BOING_LASER_EXPLOSION, posX, posY,
                                   (direction == RIGHT ? SPEED_STRAIGHT :
                                    (direction == UPRIGHT || direction == DOWNRIGHT ? SPEED_DIAG :
                                     (direction == LEFT ? -SPEED_STRAIGHT : -SPEED_DIAG))),
                                   (direction == RIGHT || direction == LEFT ? 0 :
                                    (direction == UPRIGHT || direction == UPLEFT ? -SPEED_DIAG : SPEED_DIAG)),
                                   1, 2, playerId),
            _direction(direction),
            _boingCount(0)
            {
                this->SetDamage(30);

                this->_horizontalCollisions.push_back(&BoingLaserEntity::_RightCollision);
                this->_horizontalCollisions.push_back(&BoingLaserEntity::_UpRightHorizontalCollision);
                this->_horizontalCollisions.push_back(&BoingLaserEntity::_DownRightHorizontalCollision);
                this->_horizontalCollisions.push_back(&BoingLaserEntity::_LeftCollision);
                this->_horizontalCollisions.push_back(&BoingLaserEntity::_UpLeftHorizontalCollision);
                this->_horizontalCollisions.push_back(&BoingLaserEntity::_DownLeftHorizontalCollision);

                this->_verticalCollisions.push_back(&BoingLaserEntity::_RightCollision);
                this->_verticalCollisions.push_back(&BoingLaserEntity::_UpRightVerticalCollision);
                this->_verticalCollisions.push_back(&BoingLaserEntity::_DownRightVerticalCollision);
                this->_verticalCollisions.push_back(&BoingLaserEntity::_LeftCollision);
                this->_verticalCollisions.push_back(&BoingLaserEntity::_UpLeftVerticalCollision);
                this->_verticalCollisions.push_back(&BoingLaserEntity::_DownLeftVerticalCollision);

                this->_SetFrame();
            }

        BoingLaserEntity::~BoingLaserEntity(void)
        {
        }

        void BoingLaserEntity::_SetFrame(void)
        {
            this->_sprite.SetFrame(this->_direction == RIGHT || this->_direction == LEFT ? SP_LEFT :
                                   (this->_direction == UPLEFT || this->_direction == DOWNRIGHT ? SP_UPLEFT : SP_UPRIGHT));
        }

        bool BoingLaserEntity::Interact(WallInteraction& interaction)
        {
            if (++this->_boingCount > MAX_BOING)
            {
                delete this;
                return false;
            }
            Point const& ipos = interaction.GetPosition();
            Point const& isize = interaction.GetSize();
            Circle testArea(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 5);
            if (testArea.Intersect(Rect(ipos.x - isize.x * 0.5f, ipos.y + isize.y * 0.5f, isize.x, 1)))
            {// barre en BAS
                (this->*this->_horizontalCollisions[this->_direction])(Point(testArea.position.x, ipos.y + isize.y * 0.5));
            }
            else if (testArea.Intersect(Rect(ipos.x - isize.x * 0.5f, ipos.y - isize.y * 0.5f, isize.x, 1)))
            {// barre en HAUT
                (this->*this->_horizontalCollisions[this->_direction])(Point(testArea.position.x, ipos.y - isize.y * 0.5));
            }
            else if (testArea.Intersect(Rect(ipos.x - isize.x * 0.5f, ipos.y - isize.y * 0.5f, 1, isize.y)))
            {// barre a GAUCHE
                (this->*this->_verticalCollisions[this->_direction])(Point(ipos.x - isize.x * 0.5f, testArea.position.y));
            }
            else
            {// barre a DROITE
                (this->*this->_verticalCollisions[this->_direction])(Point(ipos.x + isize.x * 0.5f, testArea.position.y));
            }
            this->_SetFrame();
            return true;
        }

        // 16 * 18

        void BoingLaserEntity::_RightCollision(Point const& pos)
        {
            this->_direction = LEFT;
            this->_sprite.SetPositionX(pos.x - 8);
            this->_sprite.SetPositionY(pos.y);
            this->_sprite.SetSpeedX(-SPEED_STRAIGHT);
        }

        void BoingLaserEntity::_LeftCollision(Point const& pos)
        {
            this->_direction = RIGHT;
            this->_sprite.SetPositionX(pos.x + 8);
            this->_sprite.SetPositionY(pos.y);
            this->_sprite.SetSpeedX(SPEED_STRAIGHT);
        }

        void BoingLaserEntity::_UpLeftVerticalCollision(Point const& pos)
        {
            this->_direction = UPRIGHT;
            this->_sprite.SetPositionX(pos.x + 8);
            this->_sprite.SetPositionY(pos.y - 9);
            this->_sprite.SetSpeedX(SPEED_DIAG);
            this->_sprite.SetSpeedY(-SPEED_DIAG);
        }

        void BoingLaserEntity::_UpLeftHorizontalCollision(Point const& pos)
        {
            this->_direction = DOWNLEFT;
            this->_sprite.SetPositionX(pos.x - 8);
            this->_sprite.SetPositionY(pos.y + 9);
            this->_sprite.SetSpeedX(-SPEED_DIAG);
            this->_sprite.SetSpeedY(SPEED_DIAG);
        }

        void BoingLaserEntity::_DownLeftVerticalCollision(Point const& pos)
        {
            this->_direction = DOWNRIGHT;
            this->_sprite.SetPositionX(pos.x + 8);
            this->_sprite.SetPositionY(pos.y + 9);
            this->_sprite.SetSpeedX(SPEED_DIAG);
            this->_sprite.SetSpeedY(SPEED_DIAG);
        }

        void BoingLaserEntity::_DownLeftHorizontalCollision(Point const& pos)
        {
            this->_direction = UPLEFT;
            this->_sprite.SetPositionX(pos.x - 8);
            this->_sprite.SetPositionY(pos.y - 9);
            this->_sprite.SetSpeedX(-SPEED_DIAG);
            this->_sprite.SetSpeedY(-SPEED_DIAG);
        }

        void BoingLaserEntity::_UpRightVerticalCollision(Point const& pos)
        {
            this->_direction = UPLEFT;
            this->_sprite.SetPositionX(pos.x - 8);
            this->_sprite.SetPositionY(pos.y - 9);
            this->_sprite.SetSpeedX(-SPEED_DIAG);
            this->_sprite.SetSpeedY(-SPEED_DIAG);
        }

        void BoingLaserEntity::_UpRightHorizontalCollision(Point const& pos)
        {
            this->_direction = DOWNRIGHT;
            this->_sprite.SetPositionX(pos.x + 8);
            this->_sprite.SetPositionY(pos.y + 9);
            this->_sprite.SetSpeedX(SPEED_DIAG);
            this->_sprite.SetSpeedY(SPEED_DIAG);
        }

        void BoingLaserEntity::_DownRightVerticalCollision(Point const& pos)
        {
            this->_direction = DOWNLEFT;
            this->_sprite.SetPositionX(pos.x - 8);
            this->_sprite.SetPositionY(pos.y + 9);
            this->_sprite.SetSpeedX(-SPEED_DIAG);
            this->_sprite.SetSpeedY(SPEED_DIAG);
        }

        void BoingLaserEntity::_DownRightHorizontalCollision(Point const& pos)
        {
            this->_direction = UPRIGHT;
            this->_sprite.SetPositionX(pos.x + 8);
            this->_sprite.SetPositionY(pos.y - 9);
            this->_sprite.SetSpeedX(SPEED_DIAG);
            this->_sprite.SetSpeedY(-SPEED_DIAG);
        }

        void BoingLaserEntity::_ExplodeEffects(void)
        {
            Decorator::PlaySound(this->_game, Resources::LASER);
        }

    }
}

