#ifndef __RECT_HPP__
#define __RECT_HPP__

#include "Shape.hpp"
#include "Point.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Circle;

        class Rect : public Shape
        {
        public:
            Rect(void);
            Rect(float x, float y, float w, float h);
            Rect(Point const& pos, float w, float h);
            Rect(Point const& p1, Point const& p2);
            ~Rect(void);

            Point GetTopLeft(void) const;
            Point GetTopRight(void) const;
            Point GetBottomLeft(void) const;
            Point GetBottomRight(void) const;
            Point GetCenter(void) const;

            virtual bool operator ==(Shape const& shape) const;
            virtual bool operator ==(Rect const& rect) const;
            virtual bool operator !=(Shape const& shape) const;
            virtual bool operator !=(Rect const& rect) const;

            virtual bool Intersect(Shape const& shape) const;
            virtual bool Intersect(Point const& pt) const;
            virtual bool Intersect(Rect const& rect) const;
            virtual bool Intersect(Circle const& circle) const;

            virtual bool Contain(Shape const& shape) const;
            virtual bool Contain(Circle const& circle) const;
            virtual bool Contain(Point const& point) const;
            virtual bool Contain(Rect const& rect) const;

            virtual bool IsContainedBy(Shape const& shape) const;

            virtual Shape* Clone(void) const;

        public:
            Point position;
            float width;
            float height;
        };

    }
}

#endif

