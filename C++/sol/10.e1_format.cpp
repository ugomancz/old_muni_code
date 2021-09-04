#include <vector>
#include <set>
#include <sstream>

template< typename T >
std::string format( const T &coll, char b, char e )
{
    int i = 0;
    std::ostringstream str;
    for ( const auto &e : coll )
        str << ( i++ ? ',' : b ) << " " << e;
    if ( i ) str << " " << e; else str << b << e;
    return str.str();
}

template< typename T >
std::string format( const std::vector< T > &s )
{
    return format( s, '[', ']' );
}

template< typename T >
std::string format( const std::set< T > &s )
{
    return format( s, '{', '}' );
}

#include "e1_format.cpp"
