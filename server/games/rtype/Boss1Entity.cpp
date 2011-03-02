
#include <cmath>

#include "Boss1Entity.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "MonsterInteraction.hpp"
#include "EnemyBulletEntity.hpp"
#include "BossBulletEntity.hpp"
#include "EnemyDamageInteraction.hpp"
#include "ShipInteraction.hpp"
#include "WallInteraction.hpp"
#include "Decorator.hpp"
#include "Boss1Node.hpp"
#include "ShipEntity.hpp"
#include "Utils.hpp"
#include "BgTileEntity.hpp"

namespace Gmgp
{
    namespace Server
    {

        Boss1Entity::Boss1Entity(Game& game, int level)
            : GameEntity(game, "Boss1"),
            _body(game.GetElapsedTime()),
            _tenia(game.GetElapsedTime()),
            _blink(false),
            _bodyHead(new WallInteraction),
            _bodyTop(new WallInteraction),
            _bodyDown(new WallInteraction),
            _bodyQueue(new WallInteraction),
            _maxLife(LIFE + LIFE * (level * 0.5f)),
            _teniaInteraction(new MonsterInteraction(this->_maxLife, this)),
            _inPosition(false),
            _lastHit(0),
            _state(CLOSED),
            _openTime(0),
            _shootTime(0),
            _middleEvent(false),
            _level(level)
        {
            this->_life.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BOSS_LIFE));
            this->_life.SetPositionZ(210);
            this->_game.GetItemManager().AddItem(&this->_life);

            this->_lifeCadre.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::POWER_CADRE));
            this->_lifeCadre.SetPositionZ(211);
            this->_game.GetItemManager().AddItem(&this->_lifeCadre);

            this->_body.SetResourceId(game.GetResourceManager().GetResourceId(Resources::BOSS1_BODY));
            this->_body.SetPositionX(Game::WIDTH + BODY_WIDTH * 0.5f + START_X_OFFSET);
            this->_body.SetSpeedX(-Game::WALL_SPEED);
            this->_body.SetPositionY(Game::HEIGHT * 0.5f);
            this->_game.GetItemManager().AddItem(&this->_body);

            this->_tenia.SetResourceId(game.GetResourceManager().GetResourceId(Resources::BOSS1_TENIA_CLOSED));
            this->_tenia.SetPositionX(Game::WIDTH + TENIA_X_OFFSET + TENIA_WIDTH * 0.5f + START_X_OFFSET);
            this->_tenia.SetSpeedX(-Game::WALL_SPEED);
            this->_tenia.SetPositionY(Game::HEIGHT * 0.5f - BODY_HEIGHT * 0.5f + TENIA_Y_OFFSET + TENIA_WIDTH * 0.5f);
            this->_game.GetItemManager().AddItem(&this->_tenia);

            for (size_t i = 1 ; i <= NB_NODES ; ++i)
                this->_nodes.push_back(new Boss1Node(game, i));

            this->_explosions.push_back(Resources::EXPLOSION2); // basic mob explosion
            this->_explosions.push_back(Resources::EXPLOSION7); // missile explosion
            this->_explosions.push_back(Resources::FLAME_THROWER_EXPLOSION);
            this->_explosions.push_back(Resources::EXPLOSION6); // big explosion
            this->_explosions.push_back(Resources::EXPLOSION6); // big explosion
            this->_explosions.push_back(Resources::EXPLOSION6); // big explosion
            this->_explosions.push_back(Resources::EXPLOSION8); // rtype big explosion
            this->_explosions.push_back(Resources::EXPLOSION8); // rtype big explosion
            this->_explosions.push_back(Resources::EXPLOSION8); // rtype big explosion
            this->_explosions.push_back(Resources::EXPLOSION9); // chicken big explosion
            this->_explosions.push_back(Resources::EXPLOSION9); // chicken big explosion
            this->_explosions.push_back(Resources::EXPLOSION9); // chicken big explosion
            this->_explosions.push_back(Resources::SMOKE);

            reinterpret_cast<WallInteraction*>(this->_bodyHead.Get())->SetSize(93, 29);
            reinterpret_cast<WallInteraction*>(this->_bodyTop.Get())->SetSize(146, 31);
            reinterpret_cast<WallInteraction*>(this->_bodyDown.Get())->SetSize(62, 105);
            reinterpret_cast<WallInteraction*>(this->_bodyQueue.Get())->SetSize(81, 22);
        }

        Boss1Entity::~Boss1Entity()
        {
            if (this->_state != DEAD)
            {
                this->_game.GetItemManager().RemoveItem(&this->_life);
                this->_game.GetItemManager().RemoveItem(&this->_lifeCadre);
                this->_game.GetItemManager().RemoveItem(&this->_body);
                this->_game.GetItemManager().RemoveItem(&this->_tenia);
                for (std::vector<Boss1Node*>::iterator it = this->_nodes.begin(),
                     ite = this->_nodes.end() ; it != ite ; ++it)
                    delete *it;
            }
        }

        void Boss1Entity::GenerateInteractions(float)
        {
            if (this->_state == DEAD)
                return;

            reinterpret_cast<WallInteraction*>(this->_bodyHead.Get())->SetPosition(this->_body.GetPositionX() - BODY_WIDTH * 0.5f + 18 + 93 * 0.5f,
                                                                                   this->_body.GetPositionY() - BODY_HEIGHT * 0.5f + 14 + 29 * 0.5f);
            reinterpret_cast<WallInteraction*>(this->_bodyTop.Get())->SetPosition(this->_body.GetPositionX() - BODY_WIDTH * 0.5f + 2 + 146 * 0.5f,
                                                                                  this->_body.GetPositionY() - BODY_HEIGHT * 0.5f + 43 + 31 * 0.5f);
            reinterpret_cast<WallInteraction*>(this->_bodyDown.Get())->SetPosition(this->_body.GetPositionX() - BODY_WIDTH * 0.5f + 92 + 62 * 0.5f,
                                                                                   this->_body.GetPositionY() - BODY_HEIGHT * 0.5f + 70 + 105 * 0.5f);
            reinterpret_cast<WallInteraction*>(this->_bodyQueue.Get())->SetPosition(this->_body.GetPositionX() - BODY_WIDTH * 0.5f + 53 + 81 * 0.5f,
                                                                                    this->_body.GetPositionY() - BODY_HEIGHT * 0.5f + 70 + 105 * 0.5f);
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_bodyHead,
                                                                                  Rect(this->_body.GetPositionX() - BODY_WIDTH * 0.5f + 18,
                                                                                       this->_body.GetPositionY() - BODY_HEIGHT * 0.5f + 14,
                                                                                       93, 29));
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_bodyTop,
                                                                                  Rect(this->_body.GetPositionX() - BODY_WIDTH * 0.5f + 2,
                                                                                       this->_body.GetPositionY() - BODY_HEIGHT * 0.5f + 43,
                                                                                       146, 31));
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_bodyDown,
                                                                                  Rect(this->_body.GetPositionX() - BODY_WIDTH * 0.5f + 92,
                                                                                       this->_body.GetPositionY() - BODY_HEIGHT * 0.5f + 70,
                                                                                       62, 105));
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_bodyQueue,
                                                                                  Rect(this->_body.GetPositionX() - BODY_WIDTH * 0.5f + 53,
                                                                                       this->_body.GetPositionY() - BODY_HEIGHT * 0.5f + 178,
                                                                                       81, 22));
            if (this->_state == OPENED)
            {
                this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_teniaInteraction,
                                                                                      Circle(this->_tenia.GetPositionX(),
                                                                                             this->_tenia.GetPositionY(),
                                                                                             16));
            }

            for (std::vector<Boss1Node*>::iterator it = this->_nodes.begin(),
                 ite = this->_nodes.end() ; it != ite ; ++it)
                (*it)->GenerateInteraction();
        }

        void Boss1Entity::Run(float time)
        {
            if (this->_state == DEAD)
            {
                if (time > this->_nextDeathEvent)
                {
                    this->_nextDeathEvent = time + this->_game.R() * 0.2f;
                    this->_RandomExplosion();
                }
                if (time > this->_deathTime + DEATH_TIME * 0.5f && this->_middleEvent == false)
                {
                    this->_middleEvent = true;
                    this->_game.StartWalls();
                    this->_game.StartBgTiles();
                }
                if (time > this->_deathTime + DEATH_TIME)
                {
                    this->_CallNextMap();
                    delete this;
                    return;
                }
                return;
            }

            if (reinterpret_cast<MonsterInteraction*>(this->_teniaInteraction.Get())->GetLife() <= 0)
            {
                this->_Die();
                return;
            }

            this->_MoveQueue(time);

            if (this->_inPosition == false)
            {
                if (this->_body.GetPositionX() < Game::WIDTH - BODY_WIDTH * 0.5f)
                {
                    Decorator::PlaySound(this->_game, Resources::BOSS_READY);

                    this->_body.SetPositionX(Game::WIDTH - BODY_WIDTH * 0.5f);
                    this->_body.SetSpeedX(0);
                    this->_tenia.SetPositionX(Game::WIDTH - BODY_WIDTH + TENIA_X_OFFSET + TENIA_WIDTH * 0.5f);
                    this->_tenia.SetSpeedX(0);

                    for (std::vector<Boss1Node*>::iterator it = this->_nodes.begin(),
                         ite = this->_nodes.end() ; it != ite ; ++it)
                        (*it)->StopX();

                    this->_game.StopWalls();
                    this->_game.StopBgTiles();
                    this->_game.StopMap();

                    this->_life.SetPositionX(300);
                    this->_life.SetPositionY(8);
                    this->_life.SetFrame(99);

                    this->_lifeCadre.SetPositionX(300);
                    this->_lifeCadre.SetPositionY(8);

                    this->_inPosition = true;
                    this->_openTime = this->_game.GetElapsedTime() + 8;
                    this->_shootTime = this->_game.GetElapsedTime() + 6;
                }
                return;
            }

            this->_Shoot(time);

            if (this->_blink && this->_stopBlinkTime < time)
            {
                this->_blink = false;
                this->_life.SetBlinking(0);
            }

            if (this->_state == CLOSED)
            {
                if (this->_openTime < time)
                {
                    this->_state = OPENING;
                    this->_tenia.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BOSS1_TENIA_OPEN));
                    this->_openTime = this->_game.GetElapsedTime() + 1;
                }
                return;
            }
            if (this->_state == OPENING)
            {
                if (this->_openTime < time)
                {
                    this->_state = OPENED;
                    this->_tenia.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BOSS1_TENIA_LOOP));
                }
                return;
            }
            if (this->_state == CLOSING)
            {
                if (this->_openTime < time)
                {
                    this->_state = CLOSED;
                    this->_tenia.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BOSS1_TENIA_CLOSED));
                    this->_openTime = time + 3 + this->_level / 4;
                }
                return;
            }
            // openened
            this->_game.GetEntityManager().GetInteractionManager().Interact(*this,
                                                                            Circle(this->_tenia.GetPositionX(),
                                                                                   this->_tenia.GetPositionY(),
                                                                                   18));
        }

        void Boss1Entity::_Shoot(float time)
        {
            if (this->_shootTime < time)
            {
                this->_shootTime += 0.4 + 1.6 / (this->_level == 0 ? 1 : this->_level);


                float speedX;
                float speedY;

                Point pos(Game::WIDTH - BODY_WIDTH + MOUTH_X_OFFSET,
                          Game::HEIGHT * 0.5f - BODY_HEIGHT * 0.5f + MOUTH_Y_OFFSET);
                ShipEntity* nearestPlayer;
                if ((nearestPlayer = Utils::GetNearestShipEntity(this->_game, pos)) != 0)
                {
                    pos = nearestPlayer->GetPosition() - pos;
                    pos.x -= 6;
                    float num = 1.0f / ::sqrtf((pos.x * pos.x) + (pos.y * pos.y));
                    speedX = 80 * pos.x * num;
                    speedY = 80 * pos.y * num;
                }
                else
                {
                    speedX = -80;
                    speedY = this->_game.R() * 30;
                }

                new BossBulletEntity(this->_game,
                                     InteractionPtr(new EnemyDamageInteraction(10, this)),
                                     Resources::BOSS1_BULLET,
                                     Resources::SMOKE,
                                     Game::WIDTH - BODY_WIDTH + MOUTH_X_OFFSET,
                                     Game::HEIGHT * 0.5f - BODY_HEIGHT * 0.5f + MOUTH_Y_OFFSET,
                                     speedX,
                                     speedY,
                                     8,
                                     12,
                                     this->GetPlayerId()
                                    );
            Decorator::PlaySound(this->_game, Resources::BOSS_FIRES);

            }
        }

        void Boss1Entity::_MoveQueue(float time)
        {
            for (std::vector<Boss1Node*>::iterator it = this->_nodes.begin(),
                 ite = this->_nodes.end() ; it != ite ; ++it)
                (*it)->Move(time);
        }

        void Boss1Entity::_CallNextMap(void)
        {
            this->_game.ChangeMusic();
            this->_game.StartMap();
        }

        void Boss1Entity::_RandomExplosion(void)
        {
            Item i;
            size_t r = static_cast<size_t>(this->_game.R() * this->_explosions.size());
            if (r >= this->_explosions.size())
                r = this->_explosions.size() - 1;
            i.SetResourceId(this->_game.GetResourceManager().GetResourceId(this->_explosions[r]));
            i.SetPositionX(Game::WIDTH - this->_game.R() * BODY_WIDTH);
            i.SetPositionY(Game::HEIGHT * 0.5f - BODY_HEIGHT * 0.5f + this->_game.R() * BODY_HEIGHT);
            i.SetLifeTimeCycles(1);
            i.SetPositionZ(135);
            this->_game.GetItemManager().SendItem(i);
        }

        void Boss1Entity::_Die(void)
        {
            this->_game.Score(reinterpret_cast<MonsterInteraction*>(this->_teniaInteraction.Get())->GetLastHit(), 10000 * this->_level);

            this->_game.ChangeMusic(Resources::MUSIC);
            Decorator::PlaySound(this->_game, Resources::BOSS_DIES);

            this->_state = DEAD;
            this->_game.GetItemManager().RemoveItem(&this->_life);
            this->_game.GetItemManager().RemoveItem(&this->_lifeCadre);
            this->_game.GetItemManager().RemoveItem(&this->_body);
            this->_game.GetItemManager().RemoveItem(&this->_tenia);
            for (std::vector<Boss1Node*>::iterator it = this->_nodes.begin(),
                 ite = this->_nodes.end() ; it != ite ; ++it)
                delete *it;
            this->_deathTime = this->_game.GetElapsedTime();
            this->_nextDeathEvent = 0;

            new BgTileEntity(this->_game,
                             this->_game.GetResourceManager().GetResourceId(Resources::BGFADE_600x240),
                             Game::WIDTH + 260, // x
                             Game::HEIGHT / 2, // y
                             600, // width
                             4, // z
                             -28); // speed

            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
            this->_RandomExplosion();
        }

        bool Boss1Entity::_Damage(int damage, uint16_t playerId)
        {
            reinterpret_cast<MonsterInteraction*>(this->_teniaInteraction.Get())->Damage(damage, playerId);
            if (reinterpret_cast<MonsterInteraction*>(this->_teniaInteraction.Get())->GetLife() <= 0 || damage < 0)
            {
                this->_Die();
                return false;
            }

            this->_state = CLOSING;
            this->_tenia.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BOSS1_TENIA_CLOSE));
            this->_openTime = this->_game.GetElapsedTime() + 1;

            this->_life.SetFrame(reinterpret_cast<MonsterInteraction*>(this->_teniaInteraction.Get())->GetLife() * 100 / this->_maxLife);
            this->_life.SetBlinking(50);
            this->_blink = true;
            this->_stopBlinkTime = this->_game.GetElapsedTime() + 2;

            return true;
        }

        bool Boss1Entity::Interact(FriendlyDamageInteraction& interaction)
        {
            return this->_Damage(interaction.GetValue(), interaction.GetPlayerId());
        }

        bool Boss1Entity::Interact(ShipInteraction& interaction)
        {
            return this->_Damage(500, interaction.GetPlayerId());
        }

    }
}

