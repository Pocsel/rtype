#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "Shape.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Rect;
        class Circle;

        class Point : public Shape
        {
        public:
            Point();
            Point(float x, float y);
            ~Point();

            float GetSquaredDistance(Point const& pt) const;
            float GetDistance(Point const& pt) const;

            Point operator +(Point const& pt) const;
            void operator +=(Point const& pt);
            Point operator -(Point const& pt) const;
            void operator -=(Point const& pt);
            virtual bool operator ==(Shape const& shape) const;
            virtual bool operator ==(Point const& pt) const;
            virtual bool operator !=(Shape const& shape) const;
            virtual bool operator !=(Point const& pt) const;

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
            float x;
            float y;
        };

    }
}

#endif

