#include <cassert>

#include "Circle.hpp"
#include "Rect.hpp"

namespace Gmgp
{
    namespace Server
    {

        Circle::Circle(void) :
            position(), _radius(0), _sqRadius(0)
        {
        }

        Circle::Circle(float x, float y, float radius) :
            position(x, y), _radius(radius), _sqRadius(radius * radius)
        {
        }

        Circle::Circle(Point const& pos, float radius) :
            position(pos), _radius(radius), _sqRadius(radius * radius)
        {
        }

        Circle::~Circle(void)
        {
        }

        float Circle::GetRadius(void) const
        {
            return this->_radius;
        }

        void Circle::SetRadius(float value)
        {
            this->_radius = value;
            this->_sqRadius = value * value;
        }

        bool Circle::operator ==(Shape const& shape) const
        {
            return shape == *this;
        }

        bool Circle::operator ==(Circle const& circle) const
        {
            return this->position == circle.position && this->_radius == circle._radius;
        }

        bool Circle::operator !=(Shape const& shape) const
        {
            return shape != *this;
        }

        bool Circle::operator !=(Circle const& circle) const
        {
            return this->position != circle.position || this->_radius != circle._radius;
        }

        bool Circle::Intersect(Shape const& shape) const
        {
            return shape.Intersect(*this);
        }

        bool Circle::Intersect(Point const& pt) const
        {
            return this->position.GetSquaredDistance(pt) <= this->_sqRadius;
        }

        bool Circle::Intersect(Rect const& rect) const
        {
            return rect.Intersect(*this);
        }

        bool Circle::Intersect(Circle const& circle) const
        {
            return this->position.GetSquaredDistance(circle.position) < (this->_sqRadius + circle._sqRadius);
        }

        Shape* Circle::Clone(void) const
        {
            return new Circle(*this);
        }

        bool Circle::Contain(Shape const& shape) const
        {
            return shape.IsContainedBy(*this);
        }

        bool Circle::Contain(Circle const& circle) const
        {
            return (this->position.GetSquaredDistance(circle.position) < this->_sqRadius &&
                    (this->_sqRadius - this->position.GetSquaredDistance(circle.position)) >= circle._sqRadius);

        }

        bool Circle::Contain(Point const& pt) const
        {
            return this->position.GetSquaredDistance(pt) < this->_sqRadius;
        }

        bool Circle::Contain(Rect const& rect) const
        {
            return (this->Contain(rect.GetTopLeft()) &&
                    this->Contain(rect.GetTopRight()) &&
                    this->Contain(rect.GetBottomLeft()) &&
                    this->Contain(rect.GetBottomRight()));
        }

        bool Circle::IsContainedBy(Shape const& shape) const
        {
            return shape.Contain(*this);
        }

    }
}
