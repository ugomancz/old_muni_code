#include <vector>
#include <utility>

int &element( std::vector< int > &v, int idx )
{
    return v[ idx ];
}

int element( const std::vector< int > &v, int idx )
{
    return v[ idx ];
}

int &element( std::pair< int, int > &v, int idx )
{
    return idx == 0 ? v.first : v.second;
}

int element( const std::pair< int, int > &v, int idx )
{
    return idx == 0 ? v.first : v.second;
}

int size( const std::pair< int, int > & ) { return 2; }
int size( const std::vector< int > &v ) { return v.size(); }

#include "e3_index.cpp"
