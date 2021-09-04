#include <cmath>

struct point
{
    double x, y;
    point( double x, double y ) : x( x ), y( y ) {}
};

struct circle_radius
{
    point center;
    double radius;
    circle_radius( point c, double r ) : center( c ), radius( r ) {}
};

struct circle_point
{
    point center, perimeter;
    circle_point( point c, point p )
        : center( c ), perimeter( p )
    {}
};

double diameter( const circle_radius &c )
{
    return c.radius * 2;
}

double diameter( const circle_point &c )
{
    double dx = c.center.x - c.perimeter.x;
    double dy = c.center.y - c.perimeter.y;
    return 2 * std::sqrt( dx * dx + dy * dy );
}

#include "e1_diameter.cpp"
