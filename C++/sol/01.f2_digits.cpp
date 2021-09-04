#include "f2_digits.cpp"

std::vector< int > digits( int n, int base )
{
    assert( n >= 0 );
    std::vector< int > ds;

    while ( n > 0 )
    {
        ds.push_back( n % base );
        n /= base;
    }

    for ( int i = 0; i < int( ds.size() / 2 ); ++ i )
        std::swap( ds[ i ], ds[ ds.size() - i - 1 ] );

    return ds;
}
