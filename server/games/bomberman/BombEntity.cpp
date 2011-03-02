
#include "BombEntity.hpp"
#include "Game.hpp"
#include "BombInteraction.hpp"
#include "Decorator.hpp"

namespace Gmgp
{
    namespace Server
    {

        BombEntity::BombEntity(Game& game, uint16_t playerId, int power, float x, float y)
            : Entity(game, "Bomb", playerId),
            _sprite(game.GetElapsedTime()),
            _power(power),
            _time(game.GetElapsedTime() + TIME),
            _bombInteraction(new BombInteraction(playerId))
        {
            this->_sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BOMB));
            this->_sprite.SetPositionX(x);
            this->_sprite.SetPositionY(y);
            this->_game.GetItemManager().AddItem(&this->_sprite);
            this->_game.RegisterBombEntity(this);
            this->_game.SetWall(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), true);
        }

        BombEntity::~BombEntity(void)
        {
            this->_game.GetItemManager().RemoveItem(&this->_sprite);
            this->_game.UnregisterBombEntity(this);
            this->_game.SetWall(this->_sprite.GetPositionX(), this->_sprite.GetPositionY(), false);
        }

        void BombEntity::Run(float time)
        {
            if (time > this->_time)
            {
                this->_Explode();
                delete this;
                return;
            }
            this->_game.GetEntityManager().GetInteractionManager().Interact(*this, Point(this->_sprite.GetPositionX(),
                                                                                         this->_sprite.GetPositionY()));
        }

        void BombEntity::_Explode(void)
        {
            Decorator::PlaySound(Resources::WA_EXPLOSION1 + this->_game.R() * 3, this->_game);

            float x = this->_sprite.GetPositionX();
            float y = this->_sprite.GetPositionY();
            this->_PutExplosion(CENTER, x, y, true);

            bool keepGoing = true;
            float nuY;
            for (int i = 1 ; i <= this->_power && keepGoing ; ++i)
            { // UP
                nuY = y - (i * Game::CASE_SIZE);
                keepGoing = this->_TryCase((i == this->_power ? UP : VERTICAL), x, nuY);
            }
            keepGoing = true;
            for (int i = 1 ; i <= this->_power && keepGoing ; ++i)
            { // DOWN
                nuY = y + (i * Game::CASE_SIZE);
                keepGoing = this->_TryCase((i == this->_power ? DOWN : VERTICAL), x, nuY);
            }

            float nuX;
            keepGoing = true;
            for (int i = 1 ; i <= this->_power && keepGoing ; ++i)
            { // LEFT
                nuX = x - (i * Game::CASE_SIZE);
                keepGoing = this->_TryCase((i == this->_power ? LEFT : HORIZONTAL), nuX, y);
            }
            keepGoing = true;
            for (int i = 1 ; i <= this->_power && keepGoing ; ++i)
            { // RIGHT
                nuX = x + (i * Game::CASE_SIZE);
                keepGoing = this->_TryCase((i == this->_power ? RIGHT : HORIZONTAL), nuX, y);
            }
        }

        bool BombEntity::_TryCase(int id, float x, float y)
        {
            if (this->_game.HasWall(x, y))
            {
                this->_PutExplosion(id, x, y, false);
                return false;
            }
            this->_PutExplosion(id, x, y, true);
            return true;
        }

        void BombEntity::_PutExplosion(int id, float x, float y, bool dispSprite)
        {
            this->_game.GetEntityManager().GetInteractionManager().AddInteraction(this->_bombInteraction,
                                                                                  Circle(x, y, Game::CASE_SIZE * 0.4f));

            if (dispSprite)
            {
                Item sprite;
                sprite.SetResourceId(this->_game.GetResourceManager().GetResourceId(id));
                sprite.SetPositionX(x);
                sprite.SetPositionY(y);
                sprite.SetLifeTimeCycles(1);
                sprite.SetPositionZ(130);
                this->_game.GetItemManager().SendItem(sprite);
            }
        }

        bool BombEntity::Interact(BombInteraction&)
        {
            this->_Explode();
            delete this;
            return false;
        }

    }
}
