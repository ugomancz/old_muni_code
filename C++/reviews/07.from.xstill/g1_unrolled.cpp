/* Another exercise, another data structure. This time we will look
 * at so-called «unrolled linked lists». We will need the data
 * structure itself, with ‹begin›, ‹end›, ‹empty› and ‹push_back›
 * methods. As usual, we will store integers. The difference between
 * a ‘normal’ singly-linked list and an unrolled list is that in the
 * latter, each node stores more than one item. In this case, we
 * will use 4 items per node. Of course, the last node might only be
 * filled partially. The iterator that ‹begin› and ‹end› return
 * should at least implement dereference, pre-increment and
 * inequality, as usual. We will not provide an interface for
 * erasing elements, because that is somewhat tricky. */

#include <cassert>
#include <memory>
#include <vector>

/** V C++ typicky nedává smysl pro konstanty používat preprocesor, daleko lepší
 ** je použít (static constexpr) konstantní hodnotu. **/
#define ROLL_SIZE 4

struct unrolled_node {
    std::unique_ptr<unrolled_node> next;
    /** vector tu není dobrý nápad protože počet hodnot je fixní a navíc malý,
     ** takže je vhodné je uložit přímo **/
    std::vector<int> values;

    void put(int v) {
        assert(values.size() < ROLL_SIZE);
        values.emplace_back(v);
    }
};     /* ref: 6 lines */

struct unrolled_iterator {
    unrolled_node *node;
    int current_index;
public:
    explicit unrolled_iterator(unrolled_node *n, int i = 0) : node(n), current_index(i) {}

    unrolled_iterator &operator++() {
        current_index++;
        if (current_index == ROLL_SIZE) {
            node = node->next.get();
            current_index = 0;
        }
        return *this;
    }

    bool operator!=(const unrolled_iterator &other) const {
        return node != other.node || current_index != other.current_index;
    }

    int &operator*() { return node->values.at(current_index); }

    int operator*() const { return node->values.at(current_index); }
}; /* ref: 22 lines */

class unrolled {
    std::unique_ptr<unrolled_node> first;
    unrolled_node *last = nullptr;

public:
    unrolled_iterator begin() const {
        return unrolled_iterator(first.get());
    }

    unrolled_iterator end() const {
        /** pro přehlednost bych ten return dal na další řádek **/
        if (!last || last->values.size() == ROLL_SIZE) return unrolled_iterator(nullptr);
        return unrolled_iterator(last, static_cast<int>(last->values.size()));
    }

    bool empty() const {
        return !last;
    }

    void push_back(int v) {
        if (!last) { // list is empty
            first = std::make_unique<unrolled_node>();
            last = first.get();
            /** last->put(v) je společný pro všechny případy a mohl by tak být
             ** za ifem **/
            last->put(v);
        } else if (last->values.size() < ROLL_SIZE) { // list is not empty and node array is not full
            last->put(v);
        } else { // list is not empty and node array is full
            last->next = std::make_unique<unrolled_node>();
            last = last->next.get();
            last->put(v);
        }
    }
};           /* ref: 36 lines */

int main()
{
    /* Basic properties of an empty list. */
    unrolled u;
    assert( u.empty() );
    assert( !( u.begin() != u.end() ) );

    /* Basic properties of a non-empty list. */

    u.push_back( 3 );
    assert( !u.empty() );
    auto i = u.begin();

    assert( i != u.end() );
    ++ i;
    assert( !( i != u.end() ) );

    /* Helper function to check the content of the list. */

    auto check = [&]( int total )
    {
        int count = 0;
        for ( int x : u )
            assert( x == count++ + 3 );
        assert( count == total );
    };

    /* Add things to the list and check they are there. */

    check( 1 );

    for ( int i = 0; i < 10; ++i )
    {
        u.push_back( 4 + i );
        check( 2 + i );
    }
}
