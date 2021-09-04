#include <vector>

struct node
{
    int value;
    int left = -1, right = -1;
    node( int v ) : value( v ) {}
};

using node_pool = std::vector< node >;

class node_ref
{
    const node_pool &pool;
    int idx;
    friend class tree;
public:
    node_ref( const node_pool &p, int i ) : pool( p ), idx( i ) {}
    node_ref left()  const { return { pool, pool[ idx ].left  }; }
    node_ref right() const { return { pool, pool[ idx ].right }; }
    int value() const { return pool[ idx ].value; }
    bool valid() const { return idx >= 0; }
};

class tree
{
    node_pool _pool;
    int _root = -1;

public:
    node_ref root() const { return { _pool, _root }; }
    bool empty() const { return _root == -1; }
    node &get( node_ref n ) { return _pool[ n.idx ]; }

    void insert( node_ref what, node_ref where, int &attach )
    {
        if ( !where.valid() )
            attach = what.idx;
        else if ( what.value() < where.value() )
            return insert( what, where.left(),  get( where ).left );
        else
            return insert( what, where.right(), get( where ).right );
    }

    void insert( int v )
    {
        int id = _pool.size();
        _pool.emplace_back( v );
        return insert( { _pool, id }, root(), _root );
    }

};

#include "f3_search.cpp"
