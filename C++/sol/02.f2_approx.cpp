#include <cmath>

auto approx = []( auto f, double initial, double prec )
{
    double x = f( initial ), y;
    do
    {
        y = x;
        x = f( x );
    } while ( std::fabs( x - y ) > prec );

    return x;
};

double golden( double prec )
{
    int a = 1, b = 1;

    auto improve = [&]( double )
    {
        int c = a + b;
        a = b;
        b = c;
        return double( b ) / a;
    };

    return approx( improve, 1, prec );
}

#include "f2_approx.cpp"
