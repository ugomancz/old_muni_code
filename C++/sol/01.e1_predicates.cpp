#include "e1_predicates.cpp"

bool all_odd( const std::vector< int > &v )
{
    for ( int x : v )
        if ( x % 2 != 1 )
            return false;
    return true;
}

bool any_odd( const std::vector< int > &v )
{
    for ( int x : v )
        if ( x % 2 == 1 )
            return true;
    return false;
}

bool count_divisible( const std::vector< int > &v, int k, int n )
{
    for ( int x : v )
        if ( x % k == 0 )
            n -= 1;
    return n <= 0;
}
