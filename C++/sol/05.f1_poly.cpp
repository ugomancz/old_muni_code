#include <vector>

class poly
{
    std::vector< int > cs;
public:
    void set( int p, int c )
    {
        cs.resize( std::max( degree(), p + 1 ), 0 );
        cs[ p ] = c;
    }

    int get( int p ) const
    {
        return p < degree() ? cs[ p ] : 0;
    }

    int degree() const { return cs.size(); }

    poly operator+( const poly &o ) const
    {
        poly rv;
        for ( int i = 0; i < std::max( degree(), o.degree() ); ++i )
            rv.set( i, get( i ) + o.get( i ) );
        return rv;
    }

    poly operator*( const poly &o ) const
    {
        poly rv;
        for ( int i = 0; i < degree(); ++i )
            for ( int j = 0; j < o.degree(); ++j )
                rv.set( i + j,
                        rv.get( i + j ) + get( i ) * o.get( j ) );
        return rv;
    }

    bool operator==( const poly &o ) const
    {
        for ( int i = 0; i < std::max( degree(), o.degree() ); ++i )
            if ( get( i ) != o.get( i ) )
                return false;
        return true;
    }
};

#include "f1_poly.cpp"
