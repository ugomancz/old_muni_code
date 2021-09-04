#include <cmath>

class shape
{
public:
    virtual double perimeter() const = 0;
};

class circle : public shape
{
    double _radius;
public:
    circle( double r ) : _radius( r ) {}
    double perimeter() const override
    {
        return 8 * std::atan( 1 ) * _radius;
    }
};

class rectangle : public shape
{
    double _width, _height;
public:
    rectangle( double w, double h ) : _width( w ), _height( h ) {}
    double perimeter() const override
    {
        return 2 * _width + 2 * _height;
    }
};

#include "e2_perimeter.cpp"
