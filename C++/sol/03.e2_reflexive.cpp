#include "e2_reflexive.cpp"

relation reflexive( const relation &r )
{
    relation out = r;

    for ( auto [ x, y ] : r )
    {
        out.emplace( x, x );
        out.emplace( y, y );
    }

    return out;
}
