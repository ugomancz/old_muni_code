#include <vector>
#include <algorithm>

struct permutations
{
    struct permutation
    {
        std::vector< int > p;
        auto begin() const { return p.begin(); }
        auto end()   const { return p.end(); }
        int operator[]( int i ) const { return p[ i ]; }
    };

    struct iterator
    {
        std::vector< int > p;

        iterator &operator++()
        {
            if ( !std::next_permutation( p.begin(), p.end() ) )
                p.clear();
            return *this;
        }

        permutation operator*() const { return { p }; }

        bool operator!=( const iterator &o ) const
        {
            return p != o.p;
        }

        bool operator==( const iterator &o ) const
        {
            return p == o.p;
        }
    };

    std::vector< int > first;

    permutations( std::vector< int > v ) : first( std::move( v ) )
    {
        std::sort( first.begin(), first.end() );
    }

    iterator begin() const { return { first }; }
    iterator end()   const { return {}; }
};

#include "f3_permute.cpp"
