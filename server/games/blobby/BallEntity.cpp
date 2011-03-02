
#include "BallEntity.hpp"
#include "Game.hpp"
#include "Resources.hpp"

namespace Gmgp
{
    namespace Server
    {
        BallEntity::BallEntity(Game& game)
            : Entity(game, "Ball")
        {
            this->_ball.SetResourceId(this->_game.GetResourceManager().GetResourceId(Resources::BALL));
            this->_game.GetItemManager().AddItem(&this->_ball);
        }

        BallEntity::~BallEntity()
        {
            this->_game.GetItemManager().RemoveItem(&this->_ball);
        }

    }
}


