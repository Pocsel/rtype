
#include "Shape.hpp"

namespace Gmgp
{
    namespace Server
    {

        bool Shape::operator ==(Circle const&) const
        {
            return false;
        }

        bool Shape::operator ==(Point const&) const
        {
            return false;
        }

        bool Shape::operator ==(Rect const&) const
        {
            return false;
        }

        bool Shape::operator !=(Circle const&) const
        {
            return true;
        }

        bool Shape::operator !=(Point const&) const
        {
            return true;
        }

        bool Shape::operator !=(Rect const&) const
        {
            return true;
        }

    }
}

