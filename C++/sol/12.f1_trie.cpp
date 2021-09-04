#include <memory>
#include <vector>
#include <cassert>

using key = std::vector< bool >;

struct node
{
    std::shared_ptr< node > l, r;
    std::weak_ptr< node > up;
    node( std::shared_ptr< node > u )
        : up( u )
    {}

    bool val() const
    {
        assert( up.lock()->l.get() == this ||
                up.lock()->r.get() == this );
        return up.lock()->r.get() == this;
    }

    ::key key() const
    {
        ::key k;
        if ( up.lock() )
        {
            k = up.lock()->key();
            k.push_back( val() );
        }
        return k;
    }
};

class trie
{
    using ptr = std::shared_ptr< node >;
    ptr r;
    using ref = node &;

public:
    trie() : r( std::make_shared< node >( nullptr ) ) {}

    auto make( ptr u ) { return std::make_shared< node >( u ); }

    ptr add( ptr n, bool l )
    {
        return ( l ? n->r : n->l ) = make( n );
    }

    ptr add_amb( ptr n )
    {
        return n->r = n->l = make( n );
    }

    ptr find( key k, int idx, ptr n ) const
    {
        if ( idx == int( k.size() ) ) return n;
        return find( k, idx + 1, k[ idx ] ? n->r : n->l );
    }

    ptr find( key k ) const { return find( k, 0, r ); }
    ptr root() const { return r; }
};

#include "f1_trie.cpp"
