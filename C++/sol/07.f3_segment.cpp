#include <memory>
#include <utility>

struct segment_map
{
    struct node
    {
        std::unique_ptr< node > l, r;
        int div;
        node( int d ) : div( d ) {}
    };

    std::unique_ptr< node > root;
    int min, max;

    segment_map( int l, int u ) : min( l ), max( u ) {}

    std::pair< int, int > query( int i, node *n, int l, int u ) const
    {
        if ( !n ) return { l, u };
        if ( i <  n->div ) return query( i, n->l.get(), l, n->div );
        if ( i >= n->div ) return query( i, n->r.get(), n->div, u );
        abort();
    }

    std::pair< int, int > query( int i ) const
    {
        return query( i, root.get(), min, max );
    }

    void split( int n )
    {
        auto old_root = std::move( root );
        root = std::make_unique< node >( n );
        if ( !old_root )
            return;

        if ( old_root->div > n )
            root->r = std::move( old_root );
        else
            root->l = std::move( old_root );
    }
};

#include "f3_segment.cpp"
