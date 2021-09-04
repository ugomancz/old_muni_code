/* This exercise is worth «12 points». */

#include <cassert>
#include <vector>

/* Write a bit-packed container, ‹oct_vector›, that will hold
 * individually addressable octal digits (3-bit numbers) with a
 * vector-like interface.
 *
 * For a capacity ⟦c = 21w⟧ (where ⟦c⟧ is the number of octal
 * digits), ‹oct_vector› must not use more than ⟦8w⟧ (that is
 * ⟦8c/21⟧) bytes of storage (not counting constant overhead). When
 * calling ‹reserve›, the total capacity may be rounded to the
 * nearest higher multiple of 21 (i.e. to a capacity such that ⟦w⟧
 * is an integer).
 *
 * To store the data, use an ‹std::vector›, and make this vector
 * available (as a ‹const› reference) via ‹data()›. Make it possible
 * to construct an ‹oct_vector› from such a ‹data› vector and the
 * size of the original ‹oct_vector› from which the data came. The
 * element type of the vector is not important.
 *
 * Minimal interface: indexing (with assignment), ‹push_back›,
 * ‹reserve›, ‹capacity›, ‹pop_back›. Iterators (‹begin›, ‹end›)
 * which can be used in a range for and with ‹std::distance› (a
 * subset of the interface of an input iterator will do, with the
 * iterator typedefs, dereference, pre-increment and (in)equality).
 * */

struct oct_vector;

/* What follows are «basic» test cases for your convenience. You can
 * add additional test cases into main(): they «will not» be
 * executed during evaluation, so it is okay to submit with broken
 * main. However, make sure to «not» alter the line with the
 * prototype. */

int main()
{
    auto bytes = []( const auto &v )
    {
        return v.data().capacity() * sizeof( v.data().front() );
    };

    oct_vector a;
    const oct_vector &a_const = a;

    a.push_back( 3 );
    assert( a.capacity() <= 21 ); /* w ≤ 1 */
    assert( bytes( a )   <= 8 );  /* bytes ≤ 8w */

    a.push_back( 5 );
    assert( a_const.capacity() <= 21 ); /* w ≤ 1 */
    assert( bytes( a )         <= 8 );  /* bytes ≤ 8w */

    a.reserve( 200 );
    assert( a.capacity() <= 210 ); /* w ≤ 10 */
    assert( bytes( a )   <= 80 );  /* bytes ≤ 8w */

    assert( a_const[ 0 ] == 3 );
    assert( a[ 1 ] == 5 );
    a[ 0 ] = 7;
    assert( a[ 0 ] == 7 );
    assert( a[ 1 ] == 5 );

    a[ 0 ] = 9;
    assert( a[ 0 ] == 1 );
    assert( a[ 1 ] == 5 );

    assert( a_const.size() == 2 );
    a.pop_back();
    assert( a.size() == 1 );
    assert( a[ 0 ] == 1 );

    oct_vector b( a_const.data(), a.size() );

    a[ 0 ] = 3;
    assert( b.size() == 1 );
    assert( b[ 0 ] == 1 );
    assert( a[ 0 ] == 3 );

    assert( std::distance( a_const.begin(), a_const.end() ) == a.size() );
    a.push_back( 1 );
    assert( std::distance( a_const.begin(), a_const.end() ) == a.size() );

    for ( auto i : a )
        assert( i == 3 || i == 1 );

    return 0;
}
