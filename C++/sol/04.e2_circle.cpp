#include <cmath>

struct point
{
    double x, y;
    point( double x, double y ) : x( x ), y( y ) {}
};

struct circle
{
    point center;
    double radius;

    circle( point c, double r )
        : center( c ), radius( r )
    {}

    circle( point c, point p )
        : center( c ),
          radius( std::sqrt( std::pow( p.x - c.x, 2 ) +
                             std::pow( p.y - c.y, 2 ) ) )
    {}
};

#include "e2_circle.cpp"
