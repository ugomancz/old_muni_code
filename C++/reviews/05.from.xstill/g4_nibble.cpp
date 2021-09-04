/* In this exercise, we will implement a class that represents an
 * array of nibbles (half-bytes) stored compactly, using a byte
 * vector as backing storage. We will need 3 classes: one to
 * represent reference-like objects: ‹nibble_ref›, another for
 * pointer-like objects: ‹nibble_ptr› and finally the container to
 * hold the nibbles: ‹nibble_vec›. NB. In this exercise, we will
 * «not» consider ‹const›-ness: treat everything as mutable. */

#include <cassert>
#include <vector>
#include <cstdint>

/** matoucí název typu, naznačuje, že je to něco co *ukládá* nibble **/
enum class nibble {
    lower, upper
};

/* The ‹nibble_ref› class needs to remember a reference or a pointer
 * to the byte which contains the nibble that we refer to, and
 * whether it is the upper or the lower nibble. With that
 * information (which should be passed to it via a constructor), it
 * needs to provide:
 *
 *  • an «assignment operator» which takes an ‹uint8_t› as an
 *    argument, but only uses the lower half of that argument to
 *    overwrite the pointed-to nibble,
 *  • a «conversion operator» which allows implicit conversion of a
 *    ‹nibble_ref› to an ‹uint8_t›. */

class nibble_ref {
    uint8_t *byte;
    const nibble current_half;
public:
    nibble_ref(uint8_t *byte, const nibble half) : byte(byte), current_half(half) {}

    nibble_ref &operator=(uint8_t value) {
        /** proč je dolní nibble uložen v horní půlce uint8_t? To je celkem
         ** zvláštní. **/
        if (current_half == nibble::lower) {
            *byte |= 0xf0;
            *byte &= ((value << 4) | 0xf);
            return *this;
        }
        *byte |= 0xf;
        *byte &= (value | 0xf0);
        return *this;
    };

    operator uint8_t() const {
        if (current_half == nibble::lower) {
            return (*byte) >> 4;
        }
        return (*byte) & 15;
    }
}; /* reference implementation: 17 lines */

/* The ‹nibble_ptr› class works as a pointer. «Dereferencing» a
 * ‹nibble_ptr› should result in a ‹nibble_ref›. There is no
 * indirect access, because the target (pointed-to) type does not
 * have any fields. To make ‹nibble_ptr› more useful, it should also
 * have:
 *
 *  • a pre-increment operator, which shifts the pointer to the next
 *    nibble in memory. That is, if it points at a lower nibble,
 *    after ‹++x›, it should point to an «upper half» of the «same»
 *    byte, and after another ‹++x›, it should point to the «lower
 *    half» of the «next» byte,
 *  • an «equality comparison» operator, which checks whether two
 *    ‹nibble_ptr› instances point to the same place in memory. */

class nibble_ptr {
    uint8_t *byte;
    nibble half;
public:
    explicit nibble_ptr(uint8_t *byte, nibble half = nibble::lower) : byte(byte), half(half) {}

    nibble_ref operator*() {
        return nibble_ref(byte, half);
    }

    nibble_ptr operator++() {
        if (half == nibble::lower) {
            half = nibble::upper;
            return *this;
        }
        /** ten sizeof je zbytečný a to hned ze dvou důvodů
         ** • += dělá posun o velikost datového typu, ne o 1 byte
         ** • sizeof(uint8_t) bude skoro vždy 1 (a pokud ne, tak se to rozbije
         **   kvůli bodu 1)
         **/
        byte += 1 * sizeof(uint8_t);
        half = nibble::lower;
        return *this;
    }

    friend bool operator==(const nibble_ptr &left, const nibble_ptr &right) {
        return left.byte == right.byte && left.half == right.half;
    }

}; /* reference implementation: 18 lines */

/* And finally the ‹nibble_vec›: this class should provide 4
 * methods:
 *
 *  • ‹push_back›, which adds a nibble at the end,
 *  • ‹begin›, which returns a ‹nibble_ptr› to the first stored
 *    nibble (lower half of the first byte),
 *  • ‹end›, which returns a ‹nibble_ptr› «past» the last stored
 *    nibble (i.e. the first nibble that is not in the container),
 *    and finally
 *  • indexing operator, which returns a ‹nibble_ref›. */

class nibble_vec {
    std::vector<uint8_t> vec;
    /** nevhodný název, nic to neříká **/
    nibble setting = nibble::lower;
public:
    void push_back(const uint8_t nibble) {
        if (setting == nibble::lower) {
            vec.emplace_back(nibble << 4);
            setting = nibble::upper;
        } else {
            vec.back() |= 0xf;
            vec.back() &= (nibble | 0xf0);
            setting = nibble::lower;
        }
    }

    nibble_ptr begin() {
        return nibble_ptr(&(vec[0]), nibble::lower);
    }

    nibble_ptr end() {
        if (setting == nibble::lower) {
            return nibble_ptr(&(vec[vec.size()]), nibble::lower);
        }
        return nibble_ptr(&(vec[vec.size() - 1]), nibble::upper);
    }

    nibble_ref operator[](const size_t index) {
        return nibble_ref(&(vec[index / 2]), (index % 2 == 0) ? nibble::lower : nibble::upper);
    }
}; /* reference implementation: 16 lines */

int main()
{
    /* Create a vector and put in a single value; we did not define
     * how should an empty vector behave. */
    nibble_vec v; v.push_back( 4 );

    /* Check that we can access the stored value through ‹begin›. */

    auto ptr = v.begin();
    assert( *ptr == 4 );

    /* And that bumping the ‹ptr› gives us ‹end›. */
    ++ ptr;
    assert( ptr == v.end() );

    /* Add another time and check that things still work okay. */

    v.push_back( 5 ); ptr = v.begin();
    assert( *ptr == 4 ); ++ ptr;
    assert( *ptr == 5 ); ++ ptr;
    assert( ptr == v.end() );

    /* And another, because this is the first time we overflow into
     * the next byte. Since ‹nibble_vec› may need to re-allocate
     * storage, the ‹ptr› is invalid after the ‹push_back›! */

    v.push_back( 6 ); ptr = v.begin();
    assert( *ptr == 4 ); ++ ptr;
    assert( *ptr == 5 ); ++ ptr;
    assert( *ptr == 6 ); ++ ptr;
    assert( ptr == v.end() );

    /* And one last time. */

    v.push_back( 0 ); ptr = v.begin();
    assert( *ptr == 4 ); ++ ptr;
    assert( *ptr == 5 ); ++ ptr;
    assert( *ptr == 6 ); ++ ptr;
    assert( *ptr == 0 ); ++ ptr;
    assert( ptr == v.end() );

    /* Let's check that indexing works. */
    assert( v[ 0 ] == 4 );
    assert( v[ 1 ] == 5 );
    assert( v[ 2 ] == 6 );
    assert( v[ 3 ] == 0 );

    /* And finally assignment in ‹nibble_ref›. An even index first. */

    v[ 0 ] = 5;
    assert( v[ 0 ] == 5 );
    assert( v[ 1 ] == 5 );
    assert( v[ 2 ] == 6 );
    assert( v[ 3 ] == 0 );

    /* Odd indices. */

    v[ 1 ] = 1;
    assert( v[ 0 ] == 5 );
    assert( v[ 1 ] == 1 );
    assert( v[ 2 ] == 6 );
    assert( v[ 3 ] == 0 );

    /* And finally the same with the other byte. */

    v[ 2 ] = 3;
    assert( v[ 0 ] == 5 );
    assert( v[ 1 ] == 1 );
    assert( v[ 2 ] == 3 );
    assert( v[ 3 ] == 0 );

    v[ 3 ] = 1;
    assert( v[ 0 ] == 5 );
    assert( v[ 1 ] == 1 );
    assert( v[ 2 ] == 3 );
    assert( v[ 3 ] == 1 );
}
