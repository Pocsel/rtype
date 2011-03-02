#include <cmath>

#include "ShipEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "GamePlayer.hpp"
#include "Constants.hpp"
#include "FriendlyBulletEntity.hpp"
#include "TextEntity.hpp"
#include "ForceAttachInteraction.hpp"
#include "ForceControlInteraction.hpp"
#include "ForceFireInteraction.hpp"
#include "TriggerInteraction.hpp"
#include "RepulseInteraction.hpp"
#include "BonusInteraction.hpp"
#include "ForceUpgradeInteraction.hpp"
#include "ForceDowngradeInteraction.hpp"
#include "Decorator.hpp"
#include "GamePlayer.hpp"
#include "ForceEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        ShipEntity::ShipEntity(Game& game, uint16_t playerId)
            : GameEntity(game, "Ship", playerId),
            _sprite(game.GetElapsedTime()),
            _shipInteraction(new ShipInteraction(playerId, this)),
            _forceFront(new ForceAttachInteraction(playerId, true, this)),
            _forceBack(new ForceAttachInteraction(playerId, false, this)),
            _forceControl(new ForceControlInteraction(playerId, this)),
            _forceFire(new ForceFireInteraction(playerId, this)),
            _repulse(new RepulseInteraction(this)),
            _direction(CENTER), _nextDirection(CENTER), _nextDirectionTime(0),
            _loadingPower(false),
            _loadedPower(false),
            _speed(BASE_SPEED),
            _nextAutoShoot(0)
        {
            Decorator::PlaySound(this->_game, Resources::PLAYER_ONLINE);

            this->_powerSprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::POWER_EMPTY));
            this->_powerSprite.SetPositionX(Game::FULLWIDTH - 51);
            this->_powerSprite.SetPositionY(Game::FULLHEIGHT - 8);
            this->_powerSprite.SetPositionZ(249);
            this->_powerSprite.SetPlayerId(playerId);

            this->_powerLoadingSprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::POWER_LOADING));
            this->_powerLoadingSprite.SetPositionX(Game::FULLWIDTH - 51);
            this->_powerLoadingSprite.SetPositionY(Game::FULLHEIGHT - 8);
            this->_powerLoadingSprite.SetPositionZ(248);
            this->_powerLoadingSprite.SetPlayerId(playerId);

            this->_powerCadreSprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::POWER_CADRE));
            this->_powerCadreSprite.SetPositionX(Game::FULLWIDTH - 51);
            this->_powerCadreSprite.SetPositionY(Game::FULLHEIGHT - 8);
            this->_powerCadreSprite.SetPositionZ(250);
            this->_powerCadreSprite.SetPlayerId(playerId);

            this->_lives.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::LIVES));
            this->_lives.SetPositionX(Game::FULLWIDTH - 135);
            this->_lives.SetPositionY(Game::FULLHEIGHT - 8);
            this->_lives.SetPositionZ(252);
            this->_lives.SetFrame(this->_game.GetNbLives(this->GetPlayerId()));
            this->_lives.SetPlayerId(playerId);

            this->_Spawn();
            this->_game.GetItemManager().AddItem(&this->_sprite);
            this->_game.GetItemManager().AddItem(&this->_powerSprite);
            this->_game.GetItemManager().AddItem(&this->_powerLoadingSprite);
            this->_game.GetItemManager().AddItem(&this->_powerCadreSprite);
            this->_game.GetItemManager().AddItem(&this->_lives);

            this->_missiles.push_back(&ShipEntity::_ShootMissile0);
            this->_missiles.push_back(&ShipEntity::_ShootMissile1);
            this->_missiles.push_back(&ShipEntity::_ShootMissile2);
            this->_missiles.push_back(&ShipEntity::_ShootMissile3);
            this->_missiles.push_back(&ShipEntity::_ShootMissile4);
            this->_missiles.push_back(&ShipEntity::_ShootMissile5);

            this->_bonuses.push_back(&ShipEntity::_BonusForce);
            this->_bonuses.push_back(&ShipEntity::_BonusSpeed);
            this->_bonuses.push_back(&ShipEntity::_BonusForceUpgrade);
            this->_bonuses.push_back(&ShipEntity::_BonusForceUpgrade);
            this->_bonuses.push_back(&ShipEntity::_BonusForceUpgrade);
            this->_bonuses.push_back(&ShipEntity::_BonusForceUpgrade);

            this->_score = new TextEntity<GameEntity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7, this->GetPlayerId());

            this->_game.RegisterShipEntity(this);
        }

        ShipEntity::~ShipEntity(void)
        {
            this->_game.UnregisterShipEntity(this);
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
            this->_game.GetItemManager().RemoveItem(&this->_powerCadreSprite);
            this->_game.GetItemManager().RemoveItem(&this->_powerSprite);
            this->_game.GetItemManager().RemoveItem(&this->_powerLoadingSprite);
            this->_game.GetItemManager().RemoveItem(&this->_lives);
            delete this->_score;
        }

        void ShipEntity::_Spawn()
        {
            if (this->_game.GetNbLives(this->GetPlayerId()) <= 0)
                return;

            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::SHIP1 + this->GetPlayerId() % 5));
            this->_sprite.SetPositionY(100 + (this->GetPlayerId() % 5) * 10.0f);
            this->_sprite.SetPositionX(-20);
            this->_sprite.SetFrame(CENTER);
            this->_sprite.SetSpeedX(60);
            this->_sprite.SetBlinking(35);
            this->_sprite.SetResponse(true);
            this->_state = SPAWNING;
            this->_spawnTime = this->_game.GetElapsedTime();
        }

        ShipEntity::State const& ShipEntity::GetState(void) const
        {
            return this->_state;
        }

        Point ShipEntity::GetPosition(void) const
        {
            return Point(this->_sprite.GetPositionX(), this->_sprite.GetPositionY());
        }

        void ShipEntity::InfoText(String const& text)
        {
            TextEntity<GameEntity, Game>* txt = new TextEntity<GameEntity, Game>(this->_game, this->_game.GetResourceManager().GetResourceId(Resources::FONT), 7);
            txt->SetText(text);
            float x = this->_sprite.GetPositionX() < 0 ? 95 : this->_sprite.GetPositionX();
            float y = this->_sprite.GetPositionY() < 0 ? 15 : this->_sprite.GetPositionY();
            txt->SetPosition(x, y, 200);
            txt->SetBlinking(30);
            txt->EnableAutoRemove(this->_game.GetElapsedTime() + 1.5f);
            txt->SetRemoveStyle(TextEntity<GameEntity, Game>::NICE);
        }

        void ShipEntity::GenerateInteractions(float)
        {
            if (this->_state == DEAD)
                return;
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_shipInteraction, Point(this->_sprite.GetPositionX(), this->_sprite.GetPositionY()));

            reinterpret_cast<ForceAttachInteraction*>(this->_forceFront.Get())->position.x = this->_sprite.GetPositionX() + 25;
            reinterpret_cast<ForceAttachInteraction*>(this->_forceFront.Get())->position.y = this->_sprite.GetPositionY();
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_forceFront, Circle(this->_sprite.GetPositionX() + 25, this->_sprite.GetPositionY(), 16));

            reinterpret_cast<ForceAttachInteraction*>(this->_forceBack.Get())->position.x = this->_sprite.GetPositionX() - 25;
            reinterpret_cast<ForceAttachInteraction*>(this->_forceBack.Get())->position.y = this->_sprite.GetPositionY();
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_forceBack, Circle(this->_sprite.GetPositionX() - 25, this->_sprite.GetPositionY(), 16));

            reinterpret_cast<RepulseInteraction*>(this->_repulse.Get())->SetPos(Point(this->_sprite.GetPositionX(), this->_sprite.GetPositionY()));
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_repulse,
                                                                                  //Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 16));
                                                                                  Rect(this->_sprite.GetPositionX() - 32, this->_sprite.GetPositionY() - 12, 64, 24));
        }

        void ShipEntity::_UpdateScore(GamePlayer& p)
        {
            String s = p.GetScore();
            if (s != this->_score->GetText())
            {
                this->_score->SetText(s);
                this->_score->SetPosition(10, Game::HEIGHT + 8, 250);
            }
        }

        void ShipEntity::Run(float time)
        {
            try
            {
                GamePlayer& p = this->_game.GetPlayerManager().GetPlayer(this->GetPlayerId());

                this->_UpdateScore(p);

                if (this->_state == DEAD)
                {
                    if (this->_game.GetNbLives(this->GetPlayerId()) > 0)
                    {
                        this->_Spawn();
                    }
                    return;
                }

                if (this->_state == SPAWNING)
                {
                    if (this->_spawnTime + 1.5 < time)
                    {
                        this->_state = INDESTRUCTIBLE;
                        this->_sprite.SetSpeedX(0);
                        this->_sprite.SetBlinking(25);
                        this->_spawnTime = time;
                    }
                    return;
                }


                // Movement
                float speedX = ((p.KeyPressed(Key::Right) || p.KeyPressed(Key::Joy13)) ? this->_speed : 0) - ((p.KeyPressed(Key::Left) || p.KeyPressed(Key::Joy15)) ? this->_speed : 0);
                float speedY = ((p.KeyPressed(Key::Down) || p.KeyPressed(Key::Joy14)) ? this->_speed : 0) - ((p.KeyPressed(Key::Up) || p.KeyPressed(Key::Joy12)) ? this->_speed : 0);

                if (speedX != 0 && speedY != 0)
                {
                    speedX *= 0.707106781f; //  1 / RACINE(2) !! :-)
                    speedY *= 0.707106781f;
                }

                if (speedX != this->_sprite.GetSpeedX())
                {
                    this->_sprite.SetSpeedX(speedX);
                    this->_sprite.SetPositionX(this->_sprite.GetPositionX());
                    reinterpret_cast<ForceAttachInteraction*>(this->_forceFront.Get())->speed.x = (this->_sprite.GetSpeedX());
                    reinterpret_cast<ForceAttachInteraction*>(this->_forceBack.Get())->speed.x = (this->_sprite.GetSpeedX());
                }

                if (speedY != this->_sprite.GetSpeedY())
                {
                    this->_sprite.SetSpeedY(speedY);
                    this->_sprite.SetPositionY(this->_sprite.GetPositionY());
                    this->_nextDirectionTime = time + 0.09f;
                    this->_GetNextDirection();
                    reinterpret_cast<ForceAttachInteraction*>(this->_forceFront.Get())->speed.y = (this->_sprite.GetSpeedY());
                    reinterpret_cast<ForceAttachInteraction*>(this->_forceBack.Get())->speed.y = (this->_sprite.GetSpeedY());
                }

                // Launch/attract force
                if (p.KeyClicked(Key::Space) || p.KeyClicked(Key::Joy1))
                {
                    reinterpret_cast<ForceControlInteraction*>(this->_forceControl.Get())->SetPos(Point(this->_sprite.GetPositionX(), this->_sprite.GetPositionY()));
                    this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_forceControl, Circle(0, 0, 2048));
                }

                if (this->_direction != this->_nextDirection && time > this->_nextDirectionTime)
                {
                    this->_direction = this->_nextDirection;
                    this->_sprite.SetFrame(this->_direction);
                    this->_GetNextDirection();
                    if (this->_nextDirection != this->_direction)
                        this->_nextDirectionTime += 0.09f;
                }

                if (this->_sprite.GetPositionX() < 1)
                    this->_sprite.SetPositionX(1);
                else if (this->_sprite.GetPositionX() > Game::WIDTH - 1)
                    this->_sprite.SetPositionX(Game::WIDTH - 1);
                if (this->_sprite.GetPositionY() < 1)
                    this->_Explode();
                else if (this->_sprite.GetPositionY() > Game::HEIGHT - 1)
                    this->_Explode();


                // Shoot
                if (p.KeyPressed(Key::LControl) || p.KeyPressed(Key::RControl) || p.KeyPressed(Key::Joy2))
                {
                    if (this->_loadingPower == false)
                    {
                        this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_forceFire, Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 400));
                        this->_loadingPower = true;
                        this->_powerLoadedTime = time + POWER_LOADING_TIME;
                        this->_SetPowerSpriteLoading();
                    }
                    else if (this->_loadedPower == false && time > this->_powerLoadedTime)
                    {
                        Decorator::PlaySound(this->_game, Resources::CHARGED + this->_game.R());
                        this->_loadedPower = true;
                        this->_SetPowerSpriteFull();
                    }
                }
                else if (this->_loadingPower)
                {
                    this->_loadingPower = false;
                    this->_loadedPower = false;
                    this->_ShootMissile(POWER_LOADING_TIME + time - this->_powerLoadedTime);
                    this->_SetPowerSpriteEmpty();
                    this->_nextAutoShoot = time + 0.13;
                }
                else if (p.KeyPressed(Key::LShift) || p.KeyPressed(Key::RShift) || p.KeyPressed(Key::Joy3))
                {
                    this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_forceFire, Circle(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), 400));
                    if (time >  this->_nextAutoShoot)
                    {
                        this->_ShootMissile(0);
                        this->_nextAutoShoot = time + 0.13;
                    }
                }

                // Interact
                if (this->_state == INDESTRUCTIBLE)
                {
                    if (this->_spawnTime + 2.5 < time)
                    {
                        this->_state = ALIVE;
                        this->_sprite.SetBlinking(0);
                    }
                }
                else
                    this->_game.GetEntityManager().GetInteractionManager().Interact(*this, Point(this->_sprite.GetPositionX(), this->_sprite.GetPositionY()));
            }
            catch (std::exception& ex)
            {
                Log::W(String("R-Type: running exception(ShipEntity): ") + ex.what());
            }
        }

        void ShipEntity::_SetPowerSpriteEmpty(void)
        {
            this->_powerSprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::POWER_EMPTY));
            this->_powerSprite.SetPositionZ(249);
        }

        void ShipEntity::_SetPowerSpriteLoading(void)
        {
            this->_powerLoadingSprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::POWER_LOADING));
            this->_powerLoadingSprite.SetPositionX(Game::FULLWIDTH - 51);
            this->_powerLoadingSprite.SetPositionY(Game::FULLHEIGHT - 8);
            this->_powerLoadingSprite.SetPositionZ(248);
            this->_powerLoadingSprite.SetFrame(0);
            this->_powerLoadingSprite.SetLifeTimeCycles(1);

            this->_powerSprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::POWER_FULL));
            this->_powerSprite.SetPositionZ(247);
        }

        void ShipEntity::_SetPowerSpriteFull(void)
        {
            Item e;
            e.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::POWER_FULL_EFFECT));
            e.SetPositionX(this->_sprite.GetPositionX());
            e.SetPositionY(this->_sprite.GetPositionY());
            e.SetPositionZ(this->_sprite.GetPositionZ());
            e.SetLifeTimeCycles(1);
            this->_game.GetItemManager().SendItem(e);
        }

        void ShipEntity::_ShootMissile(float power)
        {
            int p = static_cast<int>(power * 5);
            if (p > 5)
                p = 5;
            (this->*this->_missiles[p])();
        }

        void ShipEntity::_ShootMissile0(void)
        {
            new FriendlyBulletEntity(this->_game,
                                     InteractionPtr(new FriendlyDamageInteraction(10, this->GetPlayerId(), this)),
                                     Resources::BULLET1,
                                     Resources::EXPLOSION1,
                                     this->_sprite.GetPositionX() + 8,
                                     this->_sprite.GetPositionY(),
                                     470,
                                     this->_sprite.GetSpeedY() * 0.2f,
                                     3,
                                     6,
                                     this->GetPlayerId()
                                    );
        }

        void ShipEntity::_ShootMissile1(void)
        {
            FriendlyBulletEntity* bullet;
            bullet = new FriendlyBulletEntity(this->_game,
                                        InteractionPtr(new FriendlyDamageInteraction(20, this->GetPlayerId(), this)),
                                        Resources::BULLET3,
                                        Resources::EXPLOSION1,
                                        this->_sprite.GetPositionX() + 8,
                                        this->_sprite.GetPositionY(),
                                        470,
                                        this->_sprite.GetSpeedY() * 0.2f,
                                        4,
                                        8,
                                        this->GetPlayerId()
                                       );
        }

        void ShipEntity::_ShootMissile2(void)
        {
            FriendlyBulletEntity* bullet;
            bullet = new FriendlyBulletEntity(this->_game,
                                        InteractionPtr(new FriendlyDamageInteraction(30, this->GetPlayerId(), this)),
                                        Resources::BULLET4,
                                        Resources::EXPLOSION1,
                                        this->_sprite.GetPositionX() + 8,
                                        this->_sprite.GetPositionY(),
                                        470,
                                        this->_sprite.GetSpeedY() * 0.2f,
                                        5,
                                        10,
                                        this->GetPlayerId()
                                       );
            bullet->SetDamage(30);
        }

        void ShipEntity::_ShootMissile3(void)
        {
            FriendlyBulletEntity* bullet;
            bullet = new FriendlyBulletEntity(this->_game,
                                        InteractionPtr(new FriendlyDamageInteraction(40, this->GetPlayerId(), this)),
                                        Resources::BULLET5,
                                        Resources::EXPLOSION1,
                                        this->_sprite.GetPositionX() + 8,
                                        this->_sprite.GetPositionY(),
                                        470,
                                        this->_sprite.GetSpeedY() * 0.2f,
                                        6,
                                        12,
                                        this->GetPlayerId()
                                       );
            bullet->SetDamage(60);
        }

        void ShipEntity::_ShootMissile4(void)
        {
            FriendlyBulletEntity* bullet;
            bullet = new FriendlyBulletEntity(this->_game,
                                        InteractionPtr(new FriendlyDamageInteraction(60, this->GetPlayerId(), this)),
                                        Resources::BULLET6,
                                        Resources::EXPLOSION5,
                                        this->_sprite.GetPositionX() + 8,
                                        this->_sprite.GetPositionY(),
                                        470,
                                        this->_sprite.GetSpeedY() * 0.2f,
                                        7,
                                        16,
                                        this->GetPlayerId()
                                       );
            bullet->SetDamage(120);
        }

        void ShipEntity::_ShootMissile5(void)
        {
            FriendlyBulletEntity* bullet;
            bullet = new FriendlyBulletEntity(this->_game,
                                        InteractionPtr(new FriendlyDamageInteraction(100, this->GetPlayerId(), this)),
                                        Resources::BULLET7,
                                        Resources::EXPLOSION5,
                                        this->_sprite.GetPositionX() + 8,
                                        this->_sprite.GetPositionY(),
                                        470,
                                        this->_sprite.GetSpeedY() * 0.2f,
                                        8,
                                        16,
                                        this->GetPlayerId()
                                       );
            bullet->SetDamage(200);
        }

        void ShipEntity::_BonusForce(int)
        {
            Decorator::PlaySound(this->_game, Resources::BONUS2);
            new ForceEntity(this->_game);
        }

        void ShipEntity::_BonusSpeed(int)
        {
            Decorator::PlaySound(this->_game, Resources::BONUS3);
            this->_speed += BONUS_SPEED;
            if (this->_speed > MAX_SPEED)
                this->_speed = MAX_SPEED;
        }

        void ShipEntity::_BonusForceUpgrade(int type)
        {
            Decorator::PlaySound(this->_game, Resources::BONUS1);
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(InteractionPtr(new ForceUpgradeInteraction(type, this->GetPlayerId(), this)),
                                                                                                 Circle(0, 0, 2048));
        }

        void ShipEntity::_GetNextDirection(void)
        {
            if (this->_sprite.GetSpeedY() == 0)
            {
                if (this->_direction == CENTER || this->_direction == DOWN1 || this->_direction == UP1)
                    this->_nextDirection = CENTER;
                else if (this->_direction == DOWN2)
                    this->_nextDirection = DOWN1;
                else
                    this->_nextDirection = UP1;
            }
            else if (this->_sprite.GetSpeedY() < 0)
            {
                if (this->_direction == UP2)
                    this->_nextDirection = UP2;
                else
                    this->_nextDirection = this->_direction + 1;
            }
            else
            {
                if (this->_direction == DOWN2)
                    this->_nextDirection = DOWN2;
                else
                    this->_nextDirection = this->_direction - 1;
            }
        }

        void ShipEntity::_Explode()
        {
            Decorator::PlaySound(this->_game, Resources::PLAYER_DIES);
            Decorator::Explosion(Resources::EXPLOSION4, *this);

            this->_state = DEAD;
            this->_sprite.SetPositionX(-10000);
            this->_sprite.SetPositionY(-10000);
            this->_sprite.SetSpeedX(0);
            this->_sprite.SetSpeedY(0);
            this->_sprite.SetAccelX(0);
            this->_sprite.SetAccelY(0);

            this->_speed = BASE_SPEED;

            this->_loadingPower = false;
            this->_SetPowerSpriteEmpty();

            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(InteractionPtr(new ForceDowngradeInteraction(this->GetPlayerId(), this)),
                                                                                  Circle(0, 0, 2048));

            this->_game.SetNbLives(this->GetPlayerId(), this->_game.GetNbLives(this->GetPlayerId()) - 1);
            this->_lives.SetFrame(this->_game.GetNbLives(this->GetPlayerId()));
        }

        bool ShipEntity::Interact(EnemyDamageInteraction&)
        {
            this->_Explode();
            return false;
        }

        bool ShipEntity::Interact(WallInteraction&)
        {
            this->_Explode();
            return false;
        }

        bool ShipEntity::Interact(MonsterInteraction&)
        {
            this->_Explode();
            return false;
        }

        bool ShipEntity::Interact(TriggerInteraction& interaction)
        {
            interaction.Activate();
            return true;
        }

        bool ShipEntity::Interact(RepulseInteraction& i)
        {
            Point const& p = i.GetPos();

            //nu
            float dx = this->_sprite.GetPositionX() - p.x;
            float dy = this->_sprite.GetPositionY() - p.y;
            float dist = ::sqrtf((dx * dx) + (dy * dy));

            if (dist == 0)
                dist = 0.0001f;

            this->_sprite.SetPositionX(this->_sprite.GetPositionX() + (dx / dist));
            this->_sprite.SetPositionY(this->_sprite.GetPositionY() + (dy / dist));

            //ol
//            this->_sprite.SetPositionX(this->_sprite.GetPositionX() + (this->_sprite.GetPositionX() - p.x) * 1.45);
//            this->_sprite.SetPositionY(this->_sprite.GetPositionY() + (this->_sprite.GetPositionY() - p.y) * 1.45);
            return true;
        }

        bool ShipEntity::Interact(BonusInteraction& i)
        {
            if (i.IsPickedUp() == false)
            {
                i.PickUp();
                (this->*this->_bonuses[i.GetType()])(i.GetType());
            }
            return true;
        }

    }
}
