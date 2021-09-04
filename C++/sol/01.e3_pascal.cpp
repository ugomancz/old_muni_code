#include "e3_pascal.cpp"

std::vector< int > pascal( int n )
{
    n --;

    std::vector< int > p;
    p.push_back( 1 ); /* n over 0 */

    for ( int k = 1; k <= n; ++ k ) /* n over 1 … n */
        p.push_back( p.back() * ( n - k + 1 ) / k );

    return p;
}
