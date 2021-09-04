#include "e3_normalize.cpp"

signal normalize( const signal &s )
{
    double m = 0;
    signal out;

    for ( double x : s )
        m = std::max( m, x );

    if ( m == 0 )
        m = 1;

    for ( double x : s )
        out.push_back( x / m );

    return out;
}
