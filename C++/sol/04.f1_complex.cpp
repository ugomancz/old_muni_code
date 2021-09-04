#include <cmath>

struct angle { double v; };

struct complex
{
    double real, imag;

    complex( double r, double i )
        : real( r ), imag( i )
    {}

    complex( double m, angle phi )
        : real( m * std::cos( phi.v ) ),
          imag( m * std::sin( phi.v ) )
    {}
};

double magnitude( double x )
{
    return std::fabs( x );
}

double norm( complex c )
{
    return c.real * c.real + c.imag * c.imag;
}

double magnitude( complex c )
{
    return std::sqrt( norm( c ) );
}

double reciprocal( double x )
{
    return 1 / x;
}

complex reciprocal( complex c )
{
    return complex(  c.real / norm( c ),
                    -c.imag / norm( c ) );
}

double arg( complex c )
{
    return std::atan2( c.real, c.imag );
}

double real( complex c ) { return c.real; }
double imag( complex c ) { return c.imag; }

#include "f1_complex.cpp"
