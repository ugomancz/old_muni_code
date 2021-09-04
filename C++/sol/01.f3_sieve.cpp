#include <vector>
#include <iostream>

int sieve( int bound )
{
    std::vector< bool > s;
    s.resize( bound + 1, true );

    for ( int i = 2; i <= bound; ++i )
        if ( s[ i ] )
            for ( int j = i + i; j <= bound; j += i )
                s[ j ] = false;

    for ( int i = bound; i > 0; --i )
        if ( s[ i ] )
            return i;

    return 0;
}

#include "f3_sieve.cpp"
