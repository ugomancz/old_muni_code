#include <map>
#include <string>

class pantry
{
public:
    std::map< std::string, int > stuff;
    int count( std::string s ) const { return stuff.at( s ); }
    void add( std::string s, int v ) { stuff[ s ] += v; }
};

class recipe
{
public:
    std::map< std::string, std::pair< int, int > > stuff;

    void add( std::string s, int v, int o = 0 )
    {
        stuff[ s ].first  += v;
        stuff[ s ].second += o;
    }
};

bool cook( pantry &p, const recipe &r, int qty )
{
    for ( const auto &[ k, v ] : r.stuff )
        if ( qty * v.first > p.count( k ) )
            return false;

    for ( const auto &[ k, v ] : r.stuff )
    {
        p.stuff[ k ] -= qty * v.first;
        if ( p.count( k ) > qty * v.second )
            p.stuff[ k ] -= qty * v.second;
    }

    return true;
}

#include "f2_cooking.cpp"
