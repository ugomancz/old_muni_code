template< typename id_t > /* id for integral domain */
class rat
{
    id_t p, q;
public:
    rat( id_t p, id_t q ) : p( p ), q( q ) {}

    bool operator==( rat r ) const { return p * r.q == r.p * q; }

    friend rat operator+( rat a, rat b )
    {
        return { a.p * b.q + b.p * a.q, a.q * b.q };
    }

    rat operator*( rat r ) const { return { p * r.p, q * r.q }; }
    rat operator/( rat r ) const { return { p * r.q, q * r.p }; }
};

class gauss
{
    int r, i;
public:
    gauss( int r, int i ) : r( r ), i( i ) {}

    gauss operator+( gauss b ) const
    {
        return { r + b.r, i + b.i };
    }

    gauss operator*( gauss b ) const
    {
        return { r * b.r - i * b.i, r * b.i + i * b.r };
    }

    bool operator==( gauss b ) const
    {
        return r == b.r && i == b.i;
    }
};

#include "e2_quot.cpp"
