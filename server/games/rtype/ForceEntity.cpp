#include "ForceEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "ForceAttachInteraction.hpp"
#include "ForceControlInteraction.hpp"
#include "ForceFireInteraction.hpp"
#include "FriendlyDamageInteraction.hpp"
#include "ShieldInteraction.hpp"
#include "FriendlyBulletEntity.hpp"
#include "ForceUpgradeInteraction.hpp"
#include "ForceDowngradeInteraction.hpp"
#include "BoingLaserEntity.hpp"
#include "ExplosiveEntity.hpp"
#include "FlameEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        ForceEntity::ForceEntity(Game& game) :
            GameEntity(game, "Force"),
            _damage(new FriendlyDamageInteraction(100, 0, this)),
            _shield(new ShieldInteraction(this)),
            _playerId(0),
            _sprite(game.GetElapsedTime()),
            _state(FREE_FRONT),
            _speed(FREE_SPEED),
            _nextFireTime(0)
        {
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE1_20x16));
            this->_sprite.SetPositionX(-20);
            this->_sprite.SetPositionY(Game::HEIGHT / 2);
            this->_sprite.SetPositionZ(50);
            this->_game.GetItemManager().AddItem(&this->_sprite);
            this->_NewPosition();
            this->_InitShoots();
            this->_game.RegisterForce(this);
        }

        ForceEntity::~ForceEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
            this->_game.UnregisterForce(this);
        }

        void ForceEntity::GenerateInteractions(float)
        {
            if (this->_weapon == LEVEL0)
            {
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_damage, Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 9));
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_shield, Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 9));
            }
            else if (this->_weapon == LEVEL1)
            {
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_damage, Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 12));
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_shield, Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 12));
            }
            else
            {
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_damage, Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 16));
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_shield, Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 16));
            }
        }

        void ForceEntity::_ChooseNearestTarget()
        {
            float minDist = 10000;
            std::list<Point>::iterator it = this->_attracts.begin();
            std::list<Point>::iterator itEnd = this->_attracts.end();
            for (; it != itEnd; ++it)
            {
                float dist = it->GetDistance(Point(this->_sprite.GetPositionX(), this->_sprite.GetPositionX()));
                if (dist < minDist)
                {
                    this->_target = *it;
                    minDist = dist;
                }
            }
        }

        void ForceEntity::Run(float)
        {
            this->_attracts.clear();
            this->_game.GetEntityManager().GetInteractionManager().Interact(*this, Point(this->_sprite.GetPositionX(), this->_sprite.GetPositionY()));
            this->_ChooseNearestTarget();
            if (this->_state == LAUNCHED_FRONT)
            {
                if (this->_sprite.GetSpeedX() != LAUNCH_SPEED)
                    this->_sprite.SetSpeedX(LAUNCH_SPEED);
                if (this->_sprite.GetSpeedY() != 0)
                    this->_sprite.SetSpeedY(0);
                if (this->_sprite.GetPositionX() > Game::WIDTH - 22)
                {
                    this->_sprite.SetSpeedX(0);
                    this->_state = FREE_FRONT;
                    this->_speed = FREE_SPEED;
                    this->_NewPosition();
                    if (this->_weapon != LEVEL0 && this->_weapon != LEVEL1)
                        this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE3_DEPLOYED_29x32));
                }
            }
            else if (this->_state == LAUNCHED_BACK)
            {
                if (this->_sprite.GetSpeedX() > -LAUNCH_SPEED)
                    this->_sprite.SetSpeedX(-LAUNCH_SPEED);
                if (this->_sprite.GetPositionX() < 22)
                {
                    this->_sprite.SetSpeedX(0);
                    this->_state = FREE_BACK;
                    this->_speed = FREE_SPEED;
                    this->_NewPosition();
                }
            }
            else if (this->_state == TARGET)
            {
                if (this->_MoveToTarget())
                {
                    this->_state = FREE_FRONT;
                    this->_speed = FREE_SPEED;
                    this->_NewPosition();
                }
            }
            else if (this->_state == FREE_FRONT || this->_state == FREE_BACK)
            {
                if (this->_MoveToTarget())
                    this->_NewPosition();
            }
            // anti coincage/sortie
            if (this->_sprite.GetPositionX() <= 0 || this->_sprite.GetPositionX() >= Game::WIDTH)
            {
                this->_MoveToTarget();
                this->_state = TARGET;
            }
            if (this->_sprite.GetPositionY() <= 0 || this->_sprite.GetPositionY() >= Game::HEIGHT)
            {
                this->_NewPosition();
                this->_MoveToTarget();
                this->_state = TARGET;
            }
        }

        void ForceEntity::_NewPosition()
        {
            if (this->_state == FREE_BACK)
                this->_target.x = 10 + this->_game.R() * 100;
            else
                this->_target.x = Game::WIDTH - 190 + this->_game.R() * 180;
            this->_target.y = 60 + this->_game.R() * (Game::HEIGHT - 120);
        }

        bool ForceEntity::_IsNearX(float x) const
        {
            return (x - PRECISION < this->_sprite.GetPositionX() && x + PRECISION > this->_sprite.GetPositionX());
        }

        bool ForceEntity::_IsNearY(float y) const
        {
            return (y - PRECISION < this->_sprite.GetPositionY() && y + PRECISION > this->_sprite.GetPositionY());
        }

        bool ForceEntity::_MoveToTarget()
        {
            if (this->_IsNearX(this->_target.x))
            {
                if (this->_sprite.GetSpeedX() != 0)
                    this->_sprite.SetSpeedX(0);
            }
            else if (this->_sprite.GetPositionX() > this->_target.x)
            {
                if (this->_sprite.GetSpeedX() != -this->_speed)
                    this->_sprite.SetSpeedX(-this->_speed);
            }
            else
            {
                if (this->_sprite.GetSpeedX() != this->_speed)
                    this->_sprite.SetSpeedX(this->_speed);
            }
            if (this->_IsNearY(this->_target.y))
            {
                if (this->_sprite.GetSpeedY() != 0)
                    this->_sprite.SetSpeedY(0);
            }
            else if (this->_sprite.GetPositionY() > this->_target.y)
            {
                if (this->_sprite.GetSpeedY() != -this->_speed)
                    this->_sprite.SetSpeedY(-this->_speed);
            }
            else
            {
                if (this->_sprite.GetSpeedY() != this->_speed)
                    this->_sprite.SetSpeedY(this->_speed);
            }
            return (this->_IsNearX(this->_target.x) && this->_IsNearY(this->_target.y));
        }

        void ForceEntity::_InitShoots(void)
        {
// si FORCE_DNA_STYLE > 2 (dans bonus)
//            for (unsigned int i = 0 ; i < LEVEL0 ; ++i)
//            {
//                this->_weaponDelays.push_back(0.22);
//                this->_attachedFrontShoots.push_back(&ForceEntity::_ShootNothing);
//                this->_attachedBackShoots.push_back(&ForceEntity::_ShootNothing);
//                this->_detachedShoots.push_back(&ForceEntity::_ShootNothing);
//            }

            this->_attachedFrontShoots.push_back(&ForceEntity::_ShootNothing);
            this->_attachedBackShoots.push_back(&ForceEntity::_ShootNothing);
            this->_detachedShoots.push_back(&ForceEntity::_ShootLevel0Detached);

            this->_attachedFrontShoots.push_back(&ForceEntity::_ShootLevel1AttachedFront);
            this->_attachedBackShoots.push_back(&ForceEntity::_ShootLevel1AttachedBack);
            this->_detachedShoots.push_back(&ForceEntity::_ShootLevel1Detached);

            this->_attachedFrontShoots.push_back(&ForceEntity::_ShootDnaStyleFront);
            this->_attachedBackShoots.push_back(&ForceEntity::_ShootDnaStyleBack);
            this->_detachedShoots.push_back(&ForceEntity::_ShootLevel2Detached);

            this->_attachedFrontShoots.push_back(&ForceEntity::_ShootBoingLaserFront);
            this->_attachedBackShoots.push_back(&ForceEntity::_ShootBoingLaserBack);
            this->_detachedShoots.push_back(&ForceEntity::_ShootLevel2Detached);

            this->_attachedFrontShoots.push_back(&ForceEntity::_ShootFlameThrowerFront);
            this->_attachedBackShoots.push_back(&ForceEntity::_ShootFlameThrowerBack);
            this->_detachedShoots.push_back(&ForceEntity::_ShootLevel2Detached);

            this->_attachedFrontShoots.push_back(&ForceEntity::_ShootExplosiveFront);
            this->_attachedBackShoots.push_back(&ForceEntity::_ShootExplosiveBack);
            this->_detachedShoots.push_back(&ForceEntity::_ShootLevel2Detached);

            this->_weapon = LEVEL0;
        }

        float ForceEntity::_ShootNothing(void)
        {
            return 0.20f;
        }

        float ForceEntity::_ShootLevel0Detached(void)
        {
            new FriendlyBulletEntity(this->_game,
                                     InteractionPtr(new FriendlyDamageInteraction(10, this->_playerId, this)),
                                     Resources::FORCE_BULLET_RIGHT,
                                     Resources::EXPLOSION1,
                                     this->_sprite.GetPositionX() + 5,
                                     this->_sprite.GetPositionY(),
                                     470,
                                     0,
                                     3,
                                     6,
                                     this->_playerId
                                    );
            return 0.20f;
        }

        float ForceEntity::_ShootLevel1AttachedFront(void)
        {
            new FriendlyBulletEntity(this->_game,
                                     InteractionPtr(new FriendlyDamageInteraction(10, this->_playerId, this)),
                                     Resources::FORCE_BULLET_UPRIGHT,
                                     Resources::FORCE_BULLET_UPRIGHT_EXPLOSION,
                                     this->_sprite.GetPositionX() + 4,
                                     this->_sprite.GetPositionY() - 2,
                                     370,
                                     -150,
                                     3,
                                     6,
                                     this->_playerId
                                    );
            new FriendlyBulletEntity(this->_game,
                                     InteractionPtr(new FriendlyDamageInteraction(10, this->_playerId, this)),
                                     Resources::FORCE_BULLET_DOWNRIGHT,
                                     Resources::FORCE_BULLET_DOWNRIGHT_EXPLOSION,
                                     this->_sprite.GetPositionX() + 4,
                                     this->_sprite.GetPositionY() + 2,
                                     370,
                                     150,
                                     3,
                                     6,
                                     this->_playerId
                                    );
            return 0.20f;
        }

        float ForceEntity::_ShootLevel1AttachedBack(void)
        {
            new FriendlyBulletEntity(this->_game,
                                     InteractionPtr(new FriendlyDamageInteraction(10, this->_playerId, this)),
                                     Resources::FORCE_BULLET_UPLEFT,
                                     Resources::FORCE_BULLET_UPLEFT_EXPLOSION,
                                     this->_sprite.GetPositionX() - 4,
                                     this->_sprite.GetPositionY() - 2,
                                     -370,
                                     -150,
                                     3,
                                     6,
                                     this->_playerId
                                    );
            new FriendlyBulletEntity(this->_game,
                                     InteractionPtr(new FriendlyDamageInteraction(10, this->_playerId, this)),
                                     Resources::FORCE_BULLET_DOWNLEFT,
                                     Resources::FORCE_BULLET_DOWNLEFT_EXPLOSION,
                                     this->_sprite.GetPositionX() - 4,
                                     this->_sprite.GetPositionY() + 2,
                                     -370,
                                     150,
                                     3,
                                     6,
                                     this->_playerId
                                    );
            return 0.20f;
        }

        float ForceEntity::_ShootLevel1Detached(void)
        {
            this->_ShootLevel0Detached();
            this->_ShootLevel1AttachedFront();
            return 0.20f;
        }

        float ForceEntity::_ShootLevel2Detached(void)
        {
            this->_ShootLevel1Detached();
            new FriendlyBulletEntity(this->_game,
                                     InteractionPtr(new FriendlyDamageInteraction(10, this->_playerId, this)),
                                     Resources::FORCE_BULLET_UP,
                                     Resources::FORCE_BULLET_UP_EXPLOSION,
                                     this->_sprite.GetPositionX(),
                                     this->_sprite.GetPositionY() + 5,
                                     0,
                                     -470,
                                     3,
                                     6,
                                     this->_playerId
                                    );
            new FriendlyBulletEntity(this->_game,
                                     InteractionPtr(new FriendlyDamageInteraction(10, this->_playerId, this)),
                                     Resources::FORCE_BULLET_DOWN,
                                     Resources::FORCE_BULLET_DOWN_EXPLOSION,
                                     this->_sprite.GetPositionX(),
                                     this->_sprite.GetPositionY() - 5,
                                     0,
                                     470,
                                     3,
                                     6,
                                     this->_playerId
                                    );
            return 0.20f;
        }

        float ForceEntity::_ShootDnaStyleFront(void)
        {
            FriendlyBulletEntity* bullet = new FriendlyBulletEntity(this->_game,
                                                                    InteractionPtr(new FriendlyDamageInteraction(50, this->_playerId, this)),
                                                                    Resources::DNA_STYLE_BULLET,
                                                                    Resources::DNA_STYLE_EXPLOSION,
                                                                    this->_sprite.GetPositionX() + 5,
                                                                    this->_sprite.GetPositionY(),
                                                                    320,
                                                                    0,
                                                                    16,
                                                                    18,
                                                                    this->_playerId
                                                                   );
            bullet->SetDamage(100);
            return 0.20f;
        }

        float ForceEntity::_ShootDnaStyleBack(void)
        {
            FriendlyBulletEntity* bullet = new FriendlyBulletEntity(this->_game,
                                                                    InteractionPtr(new FriendlyDamageInteraction(50, this->_playerId, this)),
                                                                    Resources::DNA_STYLE_BULLET_REVERSE,
                                                                    Resources::DNA_STYLE_EXPLOSION,
                                                                    this->_sprite.GetPositionX() - 5,
                                                                    this->_sprite.GetPositionY(),
                                                                    -320,
                                                                    0,
                                                                    16,
                                                                    18,
                                                                    this->_playerId
                                                                   );
            bullet->SetDamage(100);
            return 0.20f;
        }

        float ForceEntity::_ShootBoingLaserFront(void)
        {
            new BoingLaserEntity(this->_game,
                                 BoingLaserEntity::RIGHT,
                                 this->_sprite.GetPositionX() + 5,
                                 this->_sprite.GetPositionY(),
                                 this->_playerId);
            new BoingLaserEntity(this->_game,
                                 BoingLaserEntity::UPRIGHT,
                                 this->_sprite.GetPositionX() + 4,
                                 this->_sprite.GetPositionY() - 2,
                                 this->_playerId);
            new BoingLaserEntity(this->_game,
                                 BoingLaserEntity::DOWNRIGHT,
                                 this->_sprite.GetPositionX() + 4,
                                 this->_sprite.GetPositionY() + 2,
                                 this->_playerId);
            return 0.24f;
        }

        float ForceEntity::_ShootBoingLaserBack(void)
        {
            new BoingLaserEntity(this->_game,
                                 BoingLaserEntity::LEFT,
                                 this->_sprite.GetPositionX() - 5,
                                 this->_sprite.GetPositionY(),
                                 this->_playerId);
            new BoingLaserEntity(this->_game,
                                 BoingLaserEntity::UPLEFT,
                                 this->_sprite.GetPositionX() - 4,
                                 this->_sprite.GetPositionY() - 2,
                                 this->_playerId);
            new BoingLaserEntity(this->_game,
                                 BoingLaserEntity::DOWNLEFT,
                                 this->_sprite.GetPositionX() - 4,
                                 this->_sprite.GetPositionY() + 2,
                                 this->_playerId);
            return 0.24f;
        }

        float ForceEntity::_ShootFlameThrowerFront(void)
        {
            new FlameEntity(this->_game,
                            true,
                            this->_sprite.GetPositionX(),
                            this->_sprite.GetPositionY() - 5,
                            this->_playerId);
            new FlameEntity(this->_game,
                            false,
                            this->_sprite.GetPositionX(),
                            this->_sprite.GetPositionY() + 5,
                            this->_playerId);
            return 0.20f;
        }

        float ForceEntity::_ShootFlameThrowerBack(void)
        {
            new FlameEntity(this->_game,
                            true,
                            this->_sprite.GetPositionX(),
                            this->_sprite.GetPositionY() - 5,
                            this->_playerId);
            new FlameEntity(this->_game,
                            false,
                            this->_sprite.GetPositionX(),
                            this->_sprite.GetPositionY() + 5,
                            this->_playerId);
            return 0.20f;
        }

        float ForceEntity::_ShootExplosiveFront(void)
        {
            new ExplosiveEntity(this->_game,
                                true,
                                this->_sprite.GetPositionX() + 5,
                                this->_sprite.GetPositionY(),
                                this->_playerId);
            return 0.60f;
        }

        float ForceEntity::_ShootExplosiveBack(void)
        {
            new ExplosiveEntity(this->_game,
                                false,
                                this->_sprite.GetPositionX() - 5,
                                this->_sprite.GetPositionY(),
                                this->_playerId);
            return 0.60f;
        }

        bool ForceEntity::Interact(ForceAttachInteraction& i)
        {
            if (this->_state != LAUNCHED_FRONT && this->_state != LAUNCHED_BACK)
            {
                if (this->_playerId == i.GetPlayerId())
                {
                    if (this->_sprite.GetPositionX() != i.position.x || this->_sprite.GetSpeedX() != i.speed.x)
                    {
                        this->_sprite.SetPositionX(i.position.x);
                        this->_sprite.SetSpeedX(i.speed.x);
                    }
                    if (this->_sprite.GetPositionY() != i.position.y || this->_sprite.GetSpeedY() != i.speed.y)
                    {
                        this->_sprite.SetPositionY(i.position.y);
                        this->_sprite.SetSpeedY(i.speed.y);
                    }
                }
                else if (this->_state != ATTACHED_FRONT && this->_state != ATTACHED_BACK)
                {
                    if (this->_sprite.GetPositionX() != i.position.x || this->_sprite.GetSpeedX() != i.speed.x)
                    {
                        this->_sprite.SetPositionX(i.position.x);
                        this->_sprite.SetSpeedX(i.speed.x);
                    }
                    if (this->_sprite.GetPositionY() != i.position.y || this->_sprite.GetSpeedY() != i.speed.y)
                    {
                        this->_sprite.SetPositionY(i.position.y);
                        this->_sprite.SetSpeedY(i.speed.y);
                    }
                    if (this->_weapon != LEVEL0 && this->_weapon != LEVEL1)
                        this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE3_ATTACHED_31x28));
                    this->_playerId = i.GetPlayerId();
                    reinterpret_cast<FriendlyDamageInteraction*>(this->_damage.Get())->SetPlayerId(this->_playerId);
                    this->SetPlayerId(this->_playerId);
                }
                this->_state = (i.IsFront() ? ATTACHED_FRONT : ATTACHED_BACK);
            }
            return true;
        }

        bool ForceEntity::Interact(ForceFireInteraction& i)
        {
            if (i.GetPlayerId() == this->_playerId && this->_nextFireTime < this->_game.GetElapsedTime())
            {
                float delay;
                if (this->_state == ATTACHED_FRONT)
                {
                    delay = (this->*this->_attachedFrontShoots[this->_weapon])();
                }
                else if (this->_state == ATTACHED_BACK)
                {
                    delay = (this->*this->_attachedBackShoots[this->_weapon])();
                }
                else
                {
                    delay = (this->*this->_detachedShoots[this->_weapon])();
                }
                this->_nextFireTime += delay;
                if (this->_nextFireTime < this->_game.GetElapsedTime())
                    this->_nextFireTime = this->_game.GetElapsedTime() + delay;
            }
            return true;
        }

        bool ForceEntity::Interact(ForceControlInteraction& i)
        {
            if (this->_state == ATTACHED_FRONT && this->_playerId == i.GetPlayerId())
            {
                this->_state = LAUNCHED_FRONT;
                if (this->_weapon != LEVEL0 && this->_weapon != LEVEL1)
                    this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE3_LAUNCHED_32x24));
            }
            else if (this->_state == ATTACHED_BACK && this->_playerId == i.GetPlayerId())
            {
                this->_state = LAUNCHED_BACK;
                if (this->_weapon != LEVEL0 && this->_weapon != LEVEL1)
                    this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE3_LAUNCHED_32x24));
            }
            else if (this->_state == FREE_FRONT || this->_state == FREE_BACK || this->_state == TARGET)
            {
                this->_state = TARGET;
                this->_speed = SPEED;
                this->_attracts.push_back(i.GetPos());
            }
            return true;
        }

        bool ForceEntity::Interact(ForceUpgradeInteraction& i)
        {
            if (i.GetPlayerId() == this->_playerId)
            {
                if (this->_weapon == LEVEL0)
                {
                    this->_weapon = LEVEL1;
                    this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE2_27x22));
                }
                else
                {
                    if (this->_weapon == LEVEL1)
                    {
                        if (this->_state == ATTACHED_FRONT || this->_state == ATTACHED_BACK)
                            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE3_ATTACHED_31x28));
                        else if (this->_state == LAUNCHED_FRONT || this->_state == LAUNCHED_BACK)
                            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE3_LAUNCHED_32x24));
                        else
                            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE3_DEPLOYED_29x32));
                    }
                    this->_weapon = static_cast<Weapon>(i.GetType());
                }
            }
            return true;
        }

        bool ForceEntity::Interact(ForceDowngradeInteraction& i)
        {
            if (i.GetPlayerId() == this->_playerId)
            {
                if (this->_weapon != LEVEL0)
                {
                    this->_weapon = LEVEL0;
                    this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::FORCE1_20x16));
                }
                if (this->_state == ATTACHED_FRONT)
                {
                    this->_state = LAUNCHED_FRONT;
                }
                else if (this->_state == ATTACHED_BACK)
                {
                    this->_state = LAUNCHED_BACK;
                }
            }
            return true;
        }

    }
}

