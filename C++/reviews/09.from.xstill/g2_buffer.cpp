/* We will implement another data structure. We have not
 * demonstrated the use of non-type template parameters with class
 * template, but the principle is the same as it was in function
 * templates in ‹rel.cpp›. An additional hint: the size of an
 * ‹std::array› is a non-type template argument (of type ‹size_t›).
 * */

#include <array>
#include <vector>
#include <cassert>

/* Implement a bounded circular buffer with a fixed size, as a class
 * template with a single type argument ‹T› (which comes first) and
 * a single non-type argument ‹size› of type ‹size_t› (which comes
 * second). The class should be default-constructible and it can
 * assume that ‹T› is also default-constructible and that it can be
 * copied. The circular buffer should provide the following methods:
 *
 *  • ‹push› inserts a value at one ‘end’
 *  • ‹pop› removes and returns a value from the other ‘end’
 *  • ‹empty› which returns true if there are no items
 *  • ‹full› if there are already ‹size› items
 *
 * Calling ‹push› on a full and ‹pop› on an empty buffer is
 * undefined. Pushing new items should wrap around the end of the
 * storage and start re-using storage from the start, as long as
 * ‹pop› has been called in the meantime (i.e. the buffer is not
 * full). In other words, ‹buffer› with ‹push› and ‹pop› behave like
 * a FIFO queue which can hold at most ‹size› elements. */

template< typename T, size_t size >
class buffer {
    std::array<T,size> _buffer{};
    size_t _begin_idx = 0, _end_idx = 0;
    bool _empty = true, _full = false;
public:
    void push(T value) {
        _empty = false;
        /** o něco lepší by bylo ukládat si index % size **/
        _buffer[_end_idx % size] = value;
        _end_idx++;
        if (_end_idx % size == _begin_idx % size) {
            _full = true;
        }
    }

    T pop() {
        _full = false;
        _begin_idx++;
        if (_begin_idx % size == _end_idx % size) {
            _empty = true;
        }
        return _buffer[(_begin_idx - 1) % size];
    }

    bool empty() const {
        return _empty;
    }

    bool full() const {
        return _full;
    }
}; /* ref: 23 lines */

int main()
{
    buffer< int, 4 > b;
    buffer< std::vector< int >, 4 > c;

    const auto &const_b = b;
    assert( const_b.empty() );
    assert( !const_b.full() );

    b.push( 1 );
    assert( !b.full() );
    b.push( 2 );
    assert( !b.empty() );
    assert( !b.full() );

    assert( b.pop() == 1 );
    b.push( 3 );
    assert( !b.full() );
    b.push( 4 );

    assert( !b.full() );
    for ( int i : { 2, 3, 4, 5, 6 } )
    {
        b.push( i + 3 );
        assert( b.full() );
        assert( b.pop() == i );
        assert( !b.full() );
    }

    assert( b.pop() == 7 );
    assert( b.pop() == 8 );
    assert( b.pop() == 9 );
    assert( b.empty() );

    assert( c.empty() );
    assert( !c.full() );
    c.push( { 1, 2 } );
    c.push( { 3, 4 } );
    assert( !c.full() );
    assert( ( c.pop() == std::vector{ 1, 2 } ) );
    assert( ( c.pop() == std::vector{ 3, 4 } ) );
    assert( c.empty() );
}
