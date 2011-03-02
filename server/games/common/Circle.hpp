#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "Shape.hpp"
#include "Point.hpp"

namespace Gmgp
{
    namespace Server
    {

        class Rect;

        class Circle : public Shape
        {
        public:
            Circle(void);
            Circle(float x, float y, float radius);
            Circle(Point const& pos, float radius);
            ~Circle(void);

            float GetRadius(void) const;
            void SetRadius(float value);

            virtual bool operator ==(Shape const& shape) const;
            virtual bool operator ==(Circle const& circle) const;
            virtual bool operator !=(Shape const& shape) const;
            virtual bool operator !=(Circle const& circle) const;

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

        private:
            float _radius;
            float _sqRadius;

        };

    }
}

#endif
