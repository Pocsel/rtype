
#include "Boss1Node.hpp"
#include "Boss1Entity.hpp"
#include "WallInteraction.hpp"
#include "Game.hpp"
#include "EnemyBulletEntity.hpp"
#include "EnemyDamageInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        Boss1Node::Boss1Node(Game& game, int pos)
            : _game(game),
            _node(game.GetElapsedTime()),
            _wallInteraction(new WallInteraction),
            _moveTime(game.GetElapsedTime() + (Boss1Entity::NB_NODES - pos) * 0.12f),
            _pos(pos),
            _started(false),
            _shootTime(game.GetElapsedTime()),
            _dir(0)
        {
            if (pos == Boss1Entity::NB_NODES)
                this->_node.SetResourceId(game.GetResourceManager().GetResourceId(Resources::BOSS1_QUEUE));
            else
                this->_node.SetResourceId(game.GetResourceManager().GetResourceId(Resources::BOSS1_NODE));
            this->_node.SetPositionX(Game::WIDTH + Boss1Entity::TAIL_X_OFFSET - (pos) * Boss1Entity::NODE_WIDTH + Boss1Entity::START_X_OFFSET);
            this->_node.SetSpeedX(-Game::WALL_SPEED);
            this->_node.SetPositionY(Game::HEIGHT * 0.5f - Boss1Entity::BODY_HEIGHT * 0.5f + Boss1Entity::TAIL_Y_OFFSET);
            this->_game.GetItemManager().AddItem(&this->_node);

            reinterpret_cast<WallInteraction*>(this->_wallInteraction.Get())->SetSize(16, 16);

            this->_shoots.push_back(&Boss1Node::_ShootDown);
            this->_shoots.push_back(&Boss1Node::_ShootDownLeft);
            this->_shoots.push_back(&Boss1Node::_ShootLeft);
            this->_shoots.push_back(&Boss1Node::_ShootUpLeft);
            this->_shoots.push_back(&Boss1Node::_ShootUp);
            this->_shoots.push_back(&Boss1Node::_ShootUpLeft);
            this->_shoots.push_back(&Boss1Node::_ShootLeft);
            this->_shoots.push_back(&Boss1Node::_ShootDownLeft);
        }

        Boss1Node::~Boss1Node(void)
        {
            this->_game.GetItemManager().RemoveItem(&this->_node);
        }

        void Boss1Node::StopX(void)
        {
            this->_node.SetPositionX(Game::WIDTH - Boss1Entity::BODY_WIDTH + Boss1Entity::TAIL_X_OFFSET - this->_pos * Boss1Entity::NODE_WIDTH);
            this->_node.SetSpeedX(0);
        }

        void Boss1Node::GenerateInteraction(void)
        {
            reinterpret_cast<WallInteraction*>(this->_wallInteraction.Get())->SetPosition(this->_node.GetPositionX(),
                                                                                          this->_node.GetPositionY());
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_wallInteraction,
                                                                                  Rect(this->_node.GetPositionX() - Boss1Entity::NODE_WIDTH * 0.5f,
                                                                                       this->_node.GetPositionY() - Boss1Entity::NODE_WIDTH * 0.5f,
                                                                                       Boss1Entity::NODE_WIDTH, Boss1Entity::NODE_WIDTH));
        }

        void Boss1Node::Move(float time)
        {
            if (time > this->_moveTime)
            {
                if (this->_started)
                {
                    this->_moveTime += 1.6f;
                    this->_node.SetPositionX(this->_node.GetPositionX());
                    this->_node.SetPositionY(Game::HEIGHT * 0.5f - Boss1Entity::BODY_HEIGHT * 0.5f + Boss1Entity::TAIL_Y_OFFSET - this->_pos * 4);
                    this->_node.SetSpeedY(this->_node.GetAccelY() * 0.8f);
                    this->_node.SetAccelY(-this->_node.GetAccelY());
                }
                else
                {
                    this->_moveTime += 0.8f;
                    this->_node.SetAccelY(-(this->_pos * 8.0f));
                    this->_started = true;
                }
            }
            if (this->_pos == Boss1Entity::NB_NODES)
            {
                if (this->_shootTime < time)
                {
                    this->_Shoot();
                    this->_shootTime += 0.4f;
                }
            }
        }

        void Boss1Node::_Shoot(void)
        {
            (this->*this->_shoots[this->_dir++])();
            this->_dir &= 0x7;
        }

        void Boss1Node::_ShootDown(void)
        {
            new EnemyBulletEntity(this->_game,
                    GameEntity::InteractionPtr(new EnemyDamageInteraction(10)),
                    Resources::BULLET2,
                    Resources::EXPLOSION3,
                    this->_node.GetPositionX(),
                    this->_node.GetPositionY() + 10,
                    0,
                    100,
                    3,
                    12
                    );
        }

        void Boss1Node::_ShootDownLeft(void)
        {
            new EnemyBulletEntity(this->_game,
                    GameEntity::InteractionPtr(new EnemyDamageInteraction(10)),
                    Resources::BULLET2,
                    Resources::EXPLOSION3,
                    this->_node.GetPositionX() - 10,
                    this->_node.GetPositionY() + 10,
                    -71,
                    71,
                    3,
                    12
                    );
        }

        void Boss1Node::_ShootLeft(void)
        {
            new EnemyBulletEntity(this->_game,
                    GameEntity::InteractionPtr(new EnemyDamageInteraction(10)),
                    Resources::BULLET2,
                    Resources::EXPLOSION3,
                    this->_node.GetPositionX() - 10,
                    this->_node.GetPositionY(),
                    -100,
                    0,
                    3,
                    12
                    );
        }

        void Boss1Node::_ShootUpLeft(void)
        {
            new EnemyBulletEntity(this->_game,
                    GameEntity::InteractionPtr(new EnemyDamageInteraction(10)),
                    Resources::BULLET2,
                    Resources::EXPLOSION3,
                    this->_node.GetPositionX() - 10,
                    this->_node.GetPositionY() - 10,
                    -71,
                    -71,
                    3,
                    12
                    );
        }

        void Boss1Node::_ShootUp(void)
        {
            new EnemyBulletEntity(this->_game,
                    GameEntity::InteractionPtr(new EnemyDamageInteraction(10)),
                    Resources::BULLET2,
                    Resources::EXPLOSION3,
                    this->_node.GetPositionX(),
                    this->_node.GetPositionY() - 10,
                    0,
                    -100,
                    3,
                    12
                    );
        }

    }
}
