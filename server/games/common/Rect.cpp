#include <cassert>

#include "Rect.hpp"
#include "Circle.hpp"

namespace Gmgp
{
    namespace Server
    {

        Rect::Rect(void) :
            position(), width(0), height(0)
        {
        }

        Rect::Rect(float x, float y, float w, float h) :
            position(x, y), width(w), height(h)
        {
        }

        Rect::Rect(Point const& pos, float w, float h) :
            position(pos), width(w), height(h)
        {
        }

        Rect::Rect(Point const& p1, Point const& p2)
        {
            this->position = Point(p1.x < p2.x ? p1.x : p2.x, p1.y < p2.y ? p1.y : p2.y);
            Point br(p1.x < p2.x ? p2.x : p1.x, p1.y < p2.y ? p2.y : p1.y);
            this->width = br.x - this->position.x;
            this->height = br.y - this->position.y;
        }

        Rect::~Rect(void)
        {
        }

        Point Rect::GetTopLeft(void) const
        {
            return this->position;
        }

        Point Rect::GetTopRight(void) const
        {
            return Point(this->position.x + this->width, this->position.y);
        }

        Point Rect::GetBottomLeft(void) const
        {
            return Point(this->position.x, this->position.y + this->height);
        }

        Point Rect::GetBottomRight(void) const
        {
            return Point(this->position.x + this->width, this->position.y + this->height);
        }

        Point Rect::GetCenter(void) const
        {
            return Point(this->position.x + this->width / 2, this->position.y + this->height / 2);
        }

        bool Rect::operator ==(Shape const& shape) const
        {
            return shape == *this;
        }

        bool Rect::operator ==(Rect const& rect) const
        {
            return this->position == rect.position && this->width == rect.width && this->height == rect.height;
        }

        bool Rect::operator !=(Shape const& shape) const
        {
            return shape != *this;
        }

        bool Rect::operator !=(Rect const& rect) const
        {
            return this->position != rect.position || this->width != rect.width || this->height != rect.height;
        }

        bool Rect::Intersect(Shape const& shape) const
        {
            return shape.Intersect(*this);
        }

        bool Rect::Intersect(Point const& pt) const
        {
            return (this->position.x <= pt.x &&
                    this->position.y <= pt.y &&
                    this->position.x + this->width >= pt.x &&
                    this->position.y + this->height >= pt.y);
        }

        bool Rect::Intersect(Rect const& rect) const
        {
            return (rect.position.x < this->position.x + this->width &&
                    this->position.x < rect.position.x + rect.width &&
                    rect.position.y < this->position.y + this->height &&
                    this->position.y < rect.position.y + rect.height);
        }

        bool Rect::Intersect(Circle const& circle) const
        {
            Point n(circle.position);

            if (n.x < this->position.x)
                n.x = this->position.x;
            else if (n.x > this->position.x + this->width)
                n.x = this->position.x + this->width;

            if (n.y < this->position.y)
                n.y = this->position.y;
            else if (n.y > this->position.y + this->height)
                n.y = this->position.y + this->height;

            return circle.Intersect(n);
        }

        Shape* Rect::Clone(void) const
        {
            return new Rect(*this);
        }

        bool Rect::Contain(Shape const& shape) const
        {
            return shape.IsContainedBy(*this);
        }

        bool Rect::Contain(Circle const& circle) const
        {
            return Rect(this->position.x - circle.GetRadius(),
                        this->position.y - circle.GetRadius(),
                        this->width - circle.GetRadius()*2,
                        this->height - circle.GetRadius()*2).Contain(circle.position);
        }

        bool Rect::Contain(Point const& pt) const
        {
            return (this->position.x <= pt.x &&
                    this->position.y <= pt.y &&
                    this->position.x + this->width >= pt.x &&
                    this->position.y + this->height >= pt.y);
        }

        bool Rect::Contain(Rect const& rect) const
        {
            return (this->position.x <= rect.position.x &&
                    this->position.y <= rect.position.y &&
                    this->position.x + this->width >= rect.position.x + rect.width &&
                    this->position.y + this->height >= rect.position.y + rect.height);
        }

        bool Rect::IsContainedBy(Shape const& shape) const
        {
            return shape.Contain(*this);
        }

    }
}

