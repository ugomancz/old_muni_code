/* In this exercise, we will implement a simple data structure
 * called a «zipper» -- a sequence of items with a single «focused»
 * item. Since we can't write class templates yet, we will just
 * make a zipper of integers. Our zipper will have these operations:
 *
 *  • (constructor) constructs a singleton zipper from an integer
 *  • ‹shift_left› and ‹shift_right› move the point of focus, in
 *    O(1), to the nearest left (right) element; they return true if
 *    this was possible, otherwise they return false and do nothing
 *  • ‹insert_left› and ‹insert_right› add a new element just left
 *    (just right) of the current focus, again in O(1)
 *  • ‹focus› access the current item (read and write)
 *  • bonus: add ‹erase_left› and ‹erase_right› to remove elements
 *    around the focus (return ‹true› if this was possible), in O(1)
 */

#include <cassert>
#include <vector>

struct node {
    int value, left_idx = -1, right_idx = -1;
};

class zipper {
private:
    std::vector <node> data;
    int current_idx = -1;

    node &get_current() {
        return data.at(current_idx);
    }

    node &get_left() {
        return data.at(get_current().left_idx);
    }

    node &get_right() {
        return data.at(get_current().right_idx);
    }

public:
    explicit zipper(int value) : data(1, {value, -1, -1}), current_idx(0) {}

    bool shift_left() {
        if (get_current().left_idx != -1) {
            current_idx = get_current().left_idx;
            return true;
        }
        return false;
    }

    bool shift_right() {
        if (get_current().right_idx != -1) {
            current_idx = get_current().right_idx;
            return true;
        }
        return false;
    }

    void insert_left(int value) {
        node new_node = node{value, get_current().left_idx, current_idx};
        if (get_current().left_idx != -1) {
            get_left().right_idx = data.size();
        }
        get_current().left_idx = data.size();
        data.emplace_back(new_node);
    }

    void insert_right(int value) {
        node new_node = node{value, current_idx, get_current().right_idx};
        if (get_current().right_idx != -1) {
            get_right().left_idx = data.size();
        }
        get_current().right_idx = data.size();
        data.emplace_back(new_node);
    }

    int focus() const {
        return data.at(current_idx).value;
    }

    int &focus() {
        return data.at(current_idx).value;
    }

};

int main()
{
    zipper a( 7 ); // [7]
    const zipper &c = a;

    assert( c.focus() == 7 ); /* constant read works */
    assert( !a.shift_left() );
    assert( c.focus() == 7 );
    assert( !a.shift_right() );
    assert( c.focus() == 7 );

    a.insert_left( 3 );        // 3 [7]
    assert( c.focus() == 7 );
    assert( a.shift_left() );  // [3] 7
    assert( c.focus() == 3 );
    assert( !a.shift_left() );
    assert( a.shift_right() ); // 3 [7]
    assert( c.focus() == 7 );
    assert( !a.shift_right() );

    zipper b = a;

    a.insert_left( 2 );   // 3 2 [7]
    a.insert_right( 4 );  // 3 2 [7] 4
    a.insert_right( 11 ); // 3 2 [7] 11 4
    a.focus() = 8; /* assignment to focus() works */

    assert( c.focus() == 8 );
    assert( a.shift_right() ); // 3 2 8 [11] 4
    assert( c.focus() == 11 );
    assert( a.shift_right() ); // 3 2 8 11 [4]
    assert( !a.shift_right() );

    assert( a.shift_left() ); // 3 2 8 [11] 4
    assert( a.focus() == 11 );
    assert( a.shift_left() ); // 3 2 [8] 11 4
    assert( a.focus() == 8 );
    assert( a.shift_left() ); // 3 [2] 8 11 4
    assert( a.focus() == 2 );
    assert( a.shift_left() ); // [3] 2 8 11 4
    assert( a.focus() == 3 );
    assert( !a.shift_left() );

    assert( b.focus() == 7 );
    assert( !b.shift_right() );
}
