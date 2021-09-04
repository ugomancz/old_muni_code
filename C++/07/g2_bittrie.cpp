/* More data structures. A bit trie (or a bitwise trie, or a bitwise
 * radix tree) is a «binary» tree for encoding a set of binary
 * values, with quick insertion and lookup. Each edge in the tree
 * encodes a single bit (i.e. it carries a zero or a one). To make
 * our life easier, we will represent the keys using a vector of
 * booleans. */

#include <vector>
#include <cassert>
#include <memory>

/* The key is a sequence of bits: iteration order (left to right)
 * corresponds to a path through the trie starting from the root.
 * I.e. the leftmost bit decides whether to go left or right from
 * the root, and so on. A key is present in the trie iff it
 * describes a path to a leaf node. */

using key = std::vector<bool>;

struct trie_node {
    std::unique_ptr<trie_node> _left, _right;
    key _key;

    explicit trie_node(key k) : _key(std::move(k)) {}

}; /* ref: 5 lines */

/* For simplicity, we will not have a normal ‹insert› method.
 * Instead, the trie will expose its root node via ‹root› and allow
 * explicit creation of new nodes via ‹make›, which accepts the
 * parent node and a boolean as arguments (the latter indicating
 * whether the newly created edge represents a 0 or a 1). Both
 * ‹root› and ‹make› should return node references. Finally, add a
 * ‹has› method which will check whether a given key is present in
 * the ‹trie›. */

class trie {
    std::unique_ptr<trie_node> _root = std::make_unique<trie_node>(key());

public:
    trie_node &root() {
        return *_root;
    }

    trie_node &make(trie_node &parent, bool arg) {
        auto new_node = std::make_unique<trie_node>(parent._key);
        new_node->_key.emplace_back(arg);
        if (!arg) {
            parent._left = std::move(new_node);
            return *parent._left;
        } else {
            parent._right = std::move(new_node);
            return *parent._right;
        }
    }

    bool has(const key &k) {
        auto current_node = _root.get();
        int index = 0;
        while (index < static_cast<int>(k.size())) {
            if (!k[index] && current_node->_left) {
                current_node = current_node->_left.get();
            } else if (k[index] && current_node->_right) {
                current_node = current_node->_right.get();
            } else {
                return false;
            }
            index++;
        }
        return current_node->_key == k && !current_node->_right && !current_node->_left;
    }
}; /* ref: 21 lines */

int main()
{
    trie x;

    assert( !x.has( key{ true } ) );
    assert( !x.has( key{ false } ) );

    auto &t = x.make( x.root(), true );
    assert(  x.has( key{ true } ) );

    x.make( t, true );
    auto &tf = x.make( t, false );

    assert( !x.has( key{ true } ) );
    assert( !x.has( key{ false } ) );
    assert( !x.has( key{ false, true } ) );
    assert( !x.has( key{ false, false } ) );
    assert(  x.has( key{ true, true } ) );
    assert(  x.has( key{ true, false } ) );
    assert( !x.has( key{ true, false, true } ) );

    x.make( tf, true );
    assert(  x.has( key{ true, false, true } ) );
}
