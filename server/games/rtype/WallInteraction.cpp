
#include "WallInteraction.hpp"

namespace Gmgp
{
    namespace Server
    {

        WallInteraction::WallInteraction(void)
            : AInteraction<GameEntity>(0)
        {
        }

        WallInteraction::~WallInteraction(void)
        {
        }

        bool WallInteraction::Interact(GameEntity& entity)
        {
            return entity.Interact(*this);
        }

        void WallInteraction::SetPosition(float x, float y)
        {
            this->_pos.x = x;
            this->_pos.y = y;
        }

        Point const& WallInteraction::GetPosition(void) const
        {
            return this->_pos;
        }

        void WallInteraction::SetSize(float w, float h)
        {
            this->_size.x = w;
            this->_size.y = h;
        }

        Point const& WallInteraction::GetSize(void) const
        {
            return this->_size;
        }

    }
}
