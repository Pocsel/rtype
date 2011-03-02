#include <cassert>
#include <math.h>

#include "Point.hpp"
#include "Rect.hpp"
#include "Circle.hpp"

namespace Gmgp
{
    namespace Server
    {

        Point::Point() :
            x(0), y(0)
        {
        }

        Point::Point(float x, float y) :
            x(x), y(y)
        {
        }

        Point::~Point()
        {
        }

        float Point::GetSquaredDistance(Point const& pt) const
        {
            float distX = this->x - pt.x;
            float distY = this->y - pt.y;
            return distX * distX + distY * distY;
        }

        float Point::GetDistance(Point const& pt) const
        {
            float distX = this->x - pt.x;
            float distY = this->y - pt.y;
            return ::sqrtf(distX * distX + distY * distY);
        }

        Point Point::operator +(Point const& pt) const
        {
            return Point(this->x + pt.x, this->y + pt.y);
        }

        void Point::operator +=(Point const& pt)
        {
            this->x += pt.x;
            this->y += pt.y;
        }

        Point Point::operator -(Point const& pt) const
        {
            return Point(this->x - pt.x, this->y - pt.y);
        }

        void Point::operator -=(Point const& pt)
        {
            this->x -= pt.x;
            this->y -= pt.y;
        }

        bool Point::operator ==(Shape const& shape) const
        {
            return shape == *this;
        }

        bool Point::operator ==(Point const& pt) const
        {
            return (pt.x == this->x && pt.y == this->y);
        }

        bool Point::operator !=(Shape const& shape) const
        {
            return shape != *this;
        }

        bool Point::operator !=(Point const& pt) const
        {
            return (pt.x != this->x || pt.y != this->y);
        }

        bool Point::Intersect(Shape const& shape) const
        {
            return shape.Intersect(*this);
        }

        bool Point::Intersect(Point const& pt) const
        {
            return (pt == *this);
        }

        bool Point::Intersect(Rect const& rect) const
        {
            return rect.Intersect(*this);
        }

        bool Point::Intersect(Circle const& circle) const
        {
            return circle.Intersect(*this);
        }

        Shape* Point::Clone(void) const
        {
            return new Point(*this);
        }

        bool Point::Contain(Shape const& shape) const
        {
            return shape.IsContainedBy(*this);
        }

        bool Point::Contain(Circle const&) const
        {
            return false;
        }

        bool Point::Contain(Point const& point) const
        {
            return *this == point;
        }

        bool Point::Contain(Rect const&) const
        {
            return false;
        }

        bool Point::IsContainedBy(Shape const& shape) const
        {
            return shape.Contain(*this);
        }

    }
}

