/* The goal of this task is to implement a B+ search tree, with
 * insertion and removal of keys. Assume that both keys and values
 * can be copied and that keys can be compared using ‹<› and ‹==›.
 *
 * The ‹max_fanout› specifies the ‘branching factor’ ⟦b⟧ of the
 * tree: the maximum number of children a node can have. Each node
 * then stores at most ⟦b - 1⟧ keys. As is usual with B trees, the
 * minimum number of children for an internal node, with the
 * exception of the root, is ⟦⌈b/2⌉⟧ (the upper integral part of
 * ⟦b/2⟧). */

#include <vector>

template< typename key_t, typename value_t, int max_fanout >
struct bplus
{
    /* Insert an element, maintaining the invariants of the B+ tree.
     * Must run in expected logarithmic time in the general case and
     * worst-case logarithmic if ‹erase› has not been called on the
     * tree. Return ‹true› if the tree was changed. */

    bool insert( const key_t &, const value_t & );

    /* Erase an element from the tree. Lazy removal is permissible,
     * i.e. without rebalancing the tree. Must run in expected
     * logarithmic time. Return ‹true› if the tree was changed. */

    bool erase( const key_t & );

    /* Look up elements. The ‹at› method should throw
     * ‹std::out_of_range› if the key is not present in the tree.
     * The indexing operator should insert a default-constructed
     * value if the key is absent, and return a reference to this
     * value. */

    bool contains( const key_t & ) const;
    value_t &at( const key_t & );
    const value_t &at( const key_t & ) const;
    value_t &operator[]( const key_t & );

    /* Look up an element and return the path that leads to it in
     * the tree, i.e. the index of the child node selected during
     * lookup at each level. Return an empty path if the key is not
     * present. The fetch operation then takes a path returned by
     * ‹path› and fetches the corresponding value from the tree.
     * Please note that the paths must reflect the layout of a
     * correct B+ tree. */

    using path_t = std::vector< int >;
    path_t path( const key_t & ) const;
    const value_t &fetch( const path_t &path ) const;
};
