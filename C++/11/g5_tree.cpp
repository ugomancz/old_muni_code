#include <cassert>
#include <memory>
#include <vector>

/* Write an iterator class and 2 functions, ‹tree_begin› and
 * ‹tree_end›, which given a proper binary tree (by const reference)
 * construct an iterable range which visits each node of the tree
 * once. The iteration should proceed in-order, that is, the entire
 * left subtree is visited before the current node, and the right
 * subtree afterwards. */

template< typename value_t >
struct tree
{
    std::unique_ptr< tree > left, right;
    tree *parent = nullptr;
    value_t value;

    static auto make_tree( const tree &t, tree *parent )
    {
        return std::make_unique< tree >( t, parent );
    }

    tree( const tree &t, tree *parent )
        : left(  t.left  ? make_tree( *t.left,  this ) : nullptr ),
          right( t.right ? make_tree( *t.right, this ) : nullptr ),
          parent( parent ),
          value( t.value )
    {}

    tree( value_t value, const tree &l, const tree &r )
        : left( make_tree( l, this ) ),
          right( make_tree( r, this ) ),
          value( std::move( value ) )
    {}

    tree( value_t value )
        : value( std::move( value ) )
    {}
};

/* Given a tree ‹t›, construct the two end-points of the iterator
 * range: */

template<typename value_t>
class tree_iterator {
private:
    tree<value_t> *_current;
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = value_t;
    using pointer = value_type *;
    using reference = value_type &;

    explicit tree_iterator(tree<value_t> *ptr) : _current(ptr) {};

    value_t &operator*() {
        return _current->value;
    }

    tree_iterator &operator++() {
        if (_current->right) {
            _current = _current->right.get();
            while (_current->left) {
                _current = _current->left.get();
            }
        } else {
            auto parent = _current->parent;
            while (parent && _current == parent->right.get()) {
                _current = parent;
                parent = parent->parent;
            }
            _current = parent;
        }
        return *this;
    }

    bool operator!=(const tree_iterator<value_t> &other) {
        return _current != other._current;
    }
};

template<typename value_t>
tree_iterator<value_t> tree_begin(const tree<value_t> &t) {
    if (!t.left) {
        return tree_iterator<value_t>(t.left->parent);
    }
    auto leftmost = t.left.get();
    while (leftmost->left.get()) {
        leftmost = leftmost->left.get();
    }
    return tree_iterator<value_t>(leftmost);
}

template<typename value_t>
tree_iterator<value_t> tree_end(const tree<value_t> &) {
    return tree_iterator<value_t>(nullptr);
}

int main()
{
    using t_int = tree< int >;
    using t_dbl = tree< double >;

    t_int t_1( 7, t_int( 2 ), t_int( 3, t_int( 4 ), t_int( 5 ) ) );
    t_dbl t_2( 7, t_dbl( 2 ), t_dbl( 3, t_dbl( 4 ), t_dbl( 5 ) ) );

    std::vector< int > v_1, v_3, v_4;
    std::vector< double > v_2;

    auto copy = []( const auto &tree, auto &vec )
    {
        for ( auto i = tree_begin( tree ) ; i != tree_end( tree ); ++i )
            vec.push_back( *i );
    };

    copy( t_1, v_1 );
    copy( t_2, v_2 );

    std::vector< int > e_1{ 2, 7, 4, 3, 5 };
    std::vector< double > e_2{ 2, 7, 4, 3, 5 };

    assert( v_1 == e_1 );
    assert( v_2 == e_2 );

    t_int t_3( 6, t_int(  4, t_int( 2, t_int( 1 ), t_int( 3 ) ),
                             t_int( 5 ) ),
                  t_int( 10, t_int( 8, t_int( 7 ), t_int( 9 ) ),
                             t_int( 11 ) ) );

    std::vector< int > e_3{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    copy( t_3, v_3 );
    assert( v_3 == e_3 );

    t_int t_4( 6, t_int( 4, t_int( 2, t_int( 1 ), t_int( 3 ) ),
                            t_int( 5 ) ),
                  t_int( 8, t_int( 7 ),
                            t_int( 10, t_int( 9 ), t_int( 11 ) ) ) );

    std::vector< int > e_4{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

    copy( t_4, v_4 );
    assert( v_4 == e_4 );
}
