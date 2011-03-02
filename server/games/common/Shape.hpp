
#ifndef SHAPE_HPP_
# define SHAPE_HPP_

namespace Gmgp
{
    namespace Server
    {

        class Circle;
        class Point;
        class Rect;

        class Shape
        {
        public:
            virtual ~Shape(void) {}

            // l'operateur == est a redefinir dans les cas utiles uniquement
            // (ca ne sert a rien de redefinir circle == rect par exemple)
            virtual bool operator ==(Shape const& shape) const = 0;
            virtual bool operator ==(Circle const& circle) const;
            virtual bool operator ==(Point const& point) const;
            virtual bool operator ==(Rect const& rect) const;

            virtual bool operator !=(Shape const& shape) const = 0;
            virtual bool operator !=(Circle const& circle) const;
            virtual bool operator !=(Point const& point) const;
            virtual bool operator !=(Rect const& rect) const;

            virtual bool Intersect(Shape const& shape) const = 0;
            virtual bool Intersect(Circle const& circle) const = 0;
            virtual bool Intersect(Point const& point) const = 0;
            virtual bool Intersect(Rect const& rect) const = 0;

            virtual bool Contain(Shape const& shape) const = 0;
            virtual bool Contain(Circle const& circle) const = 0;
            virtual bool Contain(Point const& point) const = 0;
            virtual bool Contain(Rect const& rect) const = 0;

            virtual bool IsContainedBy(Shape const& shape) const = 0;

            virtual Shape* Clone(void) const = 0;
        };

    }
}

#endif // !SHAPE_HPP_
