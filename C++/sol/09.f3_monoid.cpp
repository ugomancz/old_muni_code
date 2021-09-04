#include <string>

template< typename hom_t >
struct elem
{
    std::string v;
    hom_t h;

    elem( std::string s, hom_t h ) : v( s ), h( h ) {}
    elem operator*( const elem &e ) const { return { v + e.v, h }; }
    bool operator==( const elem &e ) const { return h( v ) == h( e.v ); }
};

template< typename hom_t >
class monoid
{
    hom_t h;
public:
    monoid( hom_t h ) : h( h ) {}
    ::elem< hom_t > elem( std::string s ) { return { s, h }; }
};

#include "f3_monoid.cpp"
