#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <string>

/* Iterators, 12 points. */

/* Given the following definition of a ‹trie›, implement an input
 * iterator which iterates through all the keys present in a given
 * ‹trie› in ascending order. Dereferencing the iterator should
 * yield an ‹std::string› (returning it by value is okay).
 *
 * Notes:
 *  • the ‹->› operator is not required,
 *  • keys are ordered lexicographically (this is the default
 *    ordering of ‹std::string› values). */

template<typename Iterator>
struct Increment {
    Iterator &operator++() {
        auto &self = static_cast<Iterator &>(*this);
        self.increment();
        return self;
    }

    Iterator operator++(int) {
        auto &self = static_cast<Iterator &>(*this);
        auto copy(self);
        ++self;
        return copy;
    }
};

struct trie;
struct trie_iterator : Increment<trie_iterator>{
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename std::string;
    using pointer = value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;

    const trie * root;
    std::string stack;
    trie_iterator(const trie * r, std::string s) : root(r), stack(std::move(s)) {};
    bool operator==(const trie_iterator &other) const {
        return root == other.root && stack == other.stack;
    }

    bool operator!=(const trie_iterator &other) const {
        return !(*this == other);
    }

    reference operator*() {
        return stack;
    }

    const_reference operator*() const {
        return stack;
    }

    void increment() {
        return;
    }
};

trie_iterator trie_begin( const trie & t);
trie_iterator trie_end( const trie & t);

struct trie /* DO NOT MODIFY */
{
    using trie_ptr = std::unique_ptr< trie >;

    /* The children are sorted in ascending order (based on the next
     * character of the key). */

    std::vector< std::pair< char, trie_ptr > > children;

    /* If ‹included› is set to ‹true›, the path which leads to this
     * node corresponds to a key present in the trie.  Such nodes
     * may or may not have children. Leaf nodes may have ‹included›
     * set to ‹false› in which case their path is not included in
     * the set of keys. */

    bool included = false;

    trie( const std::vector< std::string_view > &keys )
    {
        assert( std::is_sorted( keys.begin(), keys.end() ) );

        char c = 0;
        std::vector< std::string_view > subkeys;

        for ( auto k : keys )
            if ( k.empty() )
                included = true;
            else
            {
                if ( c && k[ 0 ] != c )
                {
                    children.emplace_back( c, new trie( subkeys ) );
                    subkeys.clear();
                }
                c = k[ 0 ];
                subkeys.push_back( k.substr( 1 ) );
            }

        if ( c )
            children.emplace_back( c, new trie( subkeys ) );
    }

    auto begin() const { return trie_begin( *this ); }
    auto end()   const { return trie_end( *this ); }
};

/* What follows are «basic» test cases for your convenience. You can
 * add additional test cases into main(): they «will not» be
 * executed during evaluation, so it is okay to submit with broken
 * main. However, make sure to «not» alter the line with the
 * prototype. */

trie_iterator trie_begin( const trie & t) {
    std::string s;
    const trie * tr = &t;
    while (!tr->children.empty()) {
        s += tr->children[0].first;
        tr = tr->children[0].second.get();
    }
    return trie_iterator(&t,s);
}
trie_iterator trie_end( const trie & t) {
    return trie_iterator(&t, std::string{});
}

int main()
{
    auto equal = []( const auto &a, const auto &b )
    {
        return std::equal( a.begin(), a.end(), b.begin(), b.end() );
    };

    std::vector< std::string_view >
        k{ "hello", "world" },
        l{ "fo", "foo", "foobar", "fubar" };

    trie m( {} );
    trie n( { "" } );
    trie o( { "x" } );
    o.children[ 0 ].second->included = false;

    assert( m.begin() == m.end() );
    assert( o.begin() == o.end() );
    assert( n.begin() != n.end() );
    assert( *n.begin() == "" );
    assert( n.begin() == n.begin() );

    trie_iterator it = n.begin();
    assert( it++ == n.begin() );
    assert( it == n.end() );

    const trie_iterator it_const = n.begin();
    it = it_const;
    assert( *it_const == "" );

    assert( equal( k, trie( k ) ) );
    assert( equal( l, trie( l ) ) );

    trie k_trie( k );
    assert( std::is_sorted( k.begin(), k.end() ) );
    assert( std::is_sorted( k_trie.begin(), k_trie.end() ) );

    return 0;
}
