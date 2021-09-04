#include <map>
#include <string>

struct strmap
{
    std::map< std::string, int > m;

    int operator[]( std::string s ) const
    {
        return m.count( s ) ? m.find( s )->second : 0;
    }

    void add( std::string s )
    {
        m[ s ] ++;
    }
};

strmap digraph_freq( const std::string &s )
{
    strmap m;

    for ( size_t i = 0; i < s.size() - 1; ++i )
        if ( std::isalpha( s[ i ] ) && std::isalpha( s[ i + 1 ] ) )
            m.add( s.substr( i, 2 ) );

    return m;
}

#include "e1_digraph.cpp"
