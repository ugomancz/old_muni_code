#include <utility>   /* swap */
#include <algorithm> /* min, max */

void normalize( int &p, int &q )
{
    int a = std::max( p, q ),
        b = std::min( p, q );

    while ( b > 0 )
    {
        a = a % b;
        std::swap( a, b );
    }

    p /= a;
    q /= a;
}

#include "e2_normalize.cpp"
