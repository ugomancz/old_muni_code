#include "tree.hpp"
#include <cassert>
#include <iostream>

/* You can put implementations of non-template methods and functions
 * into this file, as you see fit. Do not put anything after the
 * ‹main› function, and make sure its prototype remains untouched.
 * Feel free to add testing code to ‹main›. */

int main() {
    tree<int> t;
    assert(t.empty());
    t.make_root(1);
    assert(!t.empty());
    assert(t.value(t.root()) == 1);

    t.add_child(t.root(), 2);
    t.add_child(t.root(), 3);
    assert(t.child_count(t.root()) == 2);
    t.add_child(t.child_at(t.root(), 0), 4);
    t.add_child(t.child_at(t.root(), 0), 5);
    t.add_child(t.child_at(t.root(), 0), 14);
    t.add_child(t.child_at(t.root(), 0), 15);
    t.add_child(t.child_at(t.root(), 1), 6);
    t.add_child(t.child_at(t.root(), 1), 7);
    t.add_child(t.child_at(t.root(), 1), 16);
    t.add_child(t.child_at(t.root(), 1), 17);
    //auto root_copy = t.root();

    /*for (int i = 0; i < t.child_count(t.root()); i++) {
        //assert(t.value(t.child_at(t.root(), i)) == i + 1);
        t.add_child(t.child_at(t.root(), i), i + 10);
    }*/

    /*t.erase_subtree(t.child_at(t.root(),2));
    assert(t.child_count(t.root()) == 3);*/
    std::cout << "CORRECT:\t 4 5 14 15 2 6 7 16 17 3 1\n";
    std::cout << "non-const:\t ";
    auto begin = tree_begin(t);
    auto end = tree_end(t);
    while (begin != end) {
        std::cout << *begin << " ";
        ++begin;
    }

    const tree<int> *t2 = (const_cast<const tree<int> *>(&t));

    std::cout << "\nconst:\t\t ";
    const_tree_iterator<tree<int>> cbegin = tree_begin(*t2);
    auto cend = tree_end(*t2);
    while (cbegin != cend) {
        std::cout << *cbegin << " ";
        ++cbegin;
    }
}
