#include <set>
#include <algorithm>

class set
{
    std::set< int > s;
public:
    void add( int x ) { s.insert( x ); }
    bool has( int x ) const { return s.find( x ) != s.end(); }

    set operator|( const set &o ) const
    {
        set r;
        std::set_union( s.begin(), s.end(),
                        o.s.begin(), o.s.end(),
                        std::inserter( r.s, r.s.begin() ) );
        return r;
    }

    set operator&( const set &o ) const
    {
        set r;
        std::set_intersection( s.begin(), s.end(),
                               o.s.begin(), o.s.end(),
                               std::inserter( r.s, r.s.begin() ) );
        return r;
    }

    set operator-( const set &o ) const
    {
        set r;
        std::set_difference( s.begin(), s.end(),
                             o.s.begin(), o.s.end(),
                             std::inserter( r.s, r.s.begin() ) );
        return r;
    }

    bool operator<=( const set &o ) const
    {
        return ( *this - o ).s.empty();
    }
};

#include "f3_set.cpp"
