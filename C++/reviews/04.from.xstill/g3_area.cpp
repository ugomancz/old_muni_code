/* Implement 2 classes which represent 2D shapes: (regular)
 * ‹polygon› and ‹circle›. Each of the shapes has 2 constructors:
 *
 *  • ‹circle› takes either 2 points (center and a point on the
 *    circle) or a point and a number (radius),
 *  • ‹polygon› takes an integer (the number of sides ≥ 3) and
 *    either two points (center and a vertex) or a single point and a
 *    number (the major radius).
 *
 * Add a toplevel function ‹area› which can compute the area of
 * either. */

#include <cassert>
#include <cmath>

struct point {
private:
/** možná radši _x, _y **/
    double x_coordinate, y_coordinate;
public:
    point(double x, double y) : x_coordinate(x), y_coordinate(y) {}

    double x() const {
        return x_coordinate;
    }

    double y() const {
        return y_coordinate;
    }
};

struct polygon {
private:
    double sides, radius;
    point center;
public:
    /** řetězení konstruktorů by bylo lepší + řádky už jsou docela dlouhé, bylo
     ** by přehlednější nemít ty inicializační sekce zarovnané s koncem hlavičky
     **/
    polygon(double sides, point center, point vertex) : sides(sides),
                                                        radius(sqrt(pow((vertex.x() - center.x()), 2) +
                                                                    pow((vertex.y() - center.y()), 2))),
                                                        center(center) {}

    polygon(double sides, point center, double radius) : sides(sides), radius(radius), center(center) {}

    double area() const {
        /** M_PI je POSIX, ne C(++) **/
        return (sides * pow(radius, 2) * sin((2 * M_PI) / sides)) / 2;
    }

};

struct circle {
private:
    point center;
    double radius;
public:
    circle(point center, point vertex) : center(center),
                                         radius(sqrt(pow((vertex.x() - center.x()), 2) +
                                                     pow((vertex.y() - center.y()), 2))) {}

    circle(point center, double radius) : center(center), radius(radius) {}

    double area() const {
        return M_PI * pow(radius, 2);
    }
};

/** bylo by lepší brát referencí (není to už úplně malá třída) **/
double area(polygon p) {
    return p.area();
}

double area(circle c) {
    return c.area();
}

int main()
{
    polygon square( 4, point( 0, 0 ),  std::sqrt( 2 ) );
    assert( std::fabs( area( square ) - 4 ) < .001 );
    polygon hexagon( 6, point( 0, 0 ), point( 0, 1 ) );
    assert( std::fabs( area( hexagon ) - 2.598 ) < .001 );
    circle c1( point( 0, 0 ), point( 1, 0 ) );
    circle c2( point( 0, 0 ), point( 2, 0 ) );
    circle c3( point( 0, 0 ), point( 1, 1 ) );
    assert( std::fabs( area( c1 ) -     3.1415 ) < .001 );
    assert( std::fabs( area( c2 ) - 4 * 3.1415 ) < .001 );
    assert( std::fabs( area( c3 ) - 2 * 3.1415 ) < .001 );
}
