/* In this exercise, we will create a fixed-size array of nibbles (half-bytes),
 * with an indexing operator and with a basic iterator. You may want to refer
 * back to ‹05/nibble.cpp› for details about operators. */

#include <cassert>
#include <cstdlib>
#include <cstdint>

/** Tohle celé je vlastně jen kód 05/nibble s drobnými úpravami a opravenými připomínkami z review **/

enum class byte_position {
    upper, lower
};

class nibble_ref {
    uint8_t *byte;
    const byte_position current_half;
public:
    nibble_ref(uint8_t *byte, const byte_position half) : byte(byte), current_half(half) {}

    nibble_ref &operator=(uint8_t value) {
        if (current_half == byte_position::upper) {
            *byte |= 0xf0;
            *byte &= ((value << 4) | 0xf);
            return *this;
        }
        *byte |= 0xf;
        *byte &= (value | 0xf0);
        return *this;
    };

    operator uint8_t() const {
        if (current_half == byte_position::upper) {
            return (*byte) >> 4;
        }
        return (*byte) & 15;
    }
};

class nibble_iterator {
    uint8_t *byte;
    byte_position half;
public:
    explicit nibble_iterator(uint8_t *byte, byte_position half = byte_position::upper) : byte(byte), half(half) {}

    nibble_ref operator*() {
        return nibble_ref(byte, half);
    }

    nibble_iterator operator++() {
        if (half == byte_position::upper) {
            half = byte_position::lower;
            return *this;
        }
        byte += 1;
        half = byte_position::upper;
        return *this;
    }

    friend bool operator!=(const nibble_iterator &left, const nibble_iterator &right) {
        return !(left.byte == right.byte && left.half == right.half);
    }

};

/* The class template ‹nibble_array› should take a single ‹size_t›-typed
 * non-type template argument. It should be possible to index the array and to
 * iterate it using a range ‹for› loop. The storage size should be the least
 * required number of bytes. Default-constructed ‹nibble_array› should have
 * zeroes in all its entries. */

template<size_t N>
class nibble_array {
    uint8_t _nib_array[(N + 1) / 2] = {0};
public:
    nibble_iterator begin() {
        return nibble_iterator(&(_nib_array[0]), byte_position::upper);
    }

    nibble_iterator end() {
        if (N % 2 == 0) {
            return nibble_iterator(&_nib_array[(N + 1) / 2], byte_position::upper);
        }
        return nibble_iterator(&(_nib_array[N / 2]), byte_position::lower);
    }

    nibble_ref operator[](const size_t index) {
        return nibble_ref(&(_nib_array[index / 2]),
                               (index % 2 == 0) ? byte_position::upper : byte_position::lower);
    }
};

int main()
{
    static_assert( sizeof( nibble_array< 4 > ) == 2 );
    static_assert( sizeof( nibble_array< 5 > ) == 3 );

    nibble_array< 4 > x;
    nibble_array< 5 > y;

    assert( x[ 0 ] == 0 );
    assert( x[ 1 ] == 0 );

    x[ 0 ] = 1;
    assert( x[ 0 ] == 1 );
    assert( x[ 1 ] == 0 );

    x[ 3 ] = 1;
    assert( x[ 0 ] == 1 );
    assert( x[ 1 ] == 0 );
    assert( x[ 2 ] == 0 );
    assert( x[ 3 ] == 1 );

    x[ 1 ] = 7;
    assert( x[ 0 ] == 1 );
    assert( x[ 1 ] == 7 );
    assert( x[ 2 ] == 0 );
    assert( x[ 3 ] == 1 );

    x[ 2 ] = 5;
    assert( x[ 0 ] == 1 );
    assert( x[ 1 ] == 7 );
    assert( x[ 2 ] == 5 );
    assert( x[ 3 ] == 1 );

    int i = 0;
    for ( int j : x )
        switch ( i++ )
        {
            case 0: assert( j == 1 ); break;
            case 1: assert( j == 7 ); break;
            case 2: assert( j == 5 ); break;
            case 3: assert( j == 1 ); break;
            default: assert( false ); break;
        }

    assert( y[ 3 ] == 0 );
    assert( y[ 4 ] == 0 );

    y[ 3 ] = 1;
    y[ 4 ] = 1;

    assert( y[ 3 ] == 1 );
    assert( y[ 4 ] == 1 );

    i = 0;
    for ( int j : y )
        if ( i++ < 3 ) assert( j == 0 );
        else assert( j == 1 );
    assert( i == 5 );
}
