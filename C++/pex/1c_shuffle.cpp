/* This exercise is worth «12 points». */

/* Implement class ‹shuffle_vec›, which stores a sequence of 32-bit
 * words (like an ‹std::vector› of ‹uint32_t›), but which provides
 * access to half-words which alternate between all the odd and all
 * the even bits in each word. In other words, iterating a sequence
 * of 3 half-words will yield these ‹uint16_t› values:
 *
 *   1. even bits of the first word,
 *   2. odd bits of the first word,
 *   3. even bits of the second word.
 *
 * Same holds for indexed access. New half-words are added to the
 * end of the sequence using a ‹push_back› method.
 *
 * In addition to half-word access (which uses the standard ‹begin›,
 * ‹end› and the indexing operator), the container should also
 * provide read-only full-word access to the data, using methods
 * ‹raw_begin› and ‹raw_end›. If the sequence contains an odd number
 * of half-words, the odd bits of the last full word should be all
 * set to 0.
 *
 * The least-significant bit is even, i.e. the bit pattern of each
 * byte is ‹10101010›, where ‹1› is odd and ‹0› is even. The
 * half-words are constructed as follows:
 *
 *  • if full word is ‹abcdefgh ijklmnop qrstuwvx αβγδεζηθ›
 *  • the even half-word is ‹bdfhjlnp rtwxβδζθ› and,
 *  • the  odd half-word is ‹acegikmo qsuvαγεη›. */

#include <vector>
#include <cstdint>
#include <cassert>

int main()
{
    shuffle_vec s;
    const shuffle_vec &cs = s;

    s.push_back( 1 );
    assert( s.begin() == s.begin() );
    assert( *s.begin() == 1 );

    *s.begin() = 3;
    assert( *s.begin() == 3 );
    assert( *cs.raw_begin() == 5 );

    s.push_back( 1 );
    assert( s[ 0 ] == 3 );
    assert( s[ 1 ] == 1 );
    assert( *s.raw_begin() == 0b111 );

    s[ 1 ] = 2;
    assert( s[ 0 ] == 3 );
    assert( s[ 1 ] == 2 );
    assert( *s.raw_begin() == 0b1101 );

    s[ 1 ] = 4;
    assert( s[ 0 ] == 3 );
    assert( s[ 1 ] == 4 );
    assert( *s.raw_begin() == 0b100101 );

    s[ 1 ] = 5;
    assert( s[ 0 ] == 3 );
    assert( s[ 1 ] == 5 );
    assert( *s.raw_begin() == 0b100111 );

    s[ 0 ] = 5;
    assert( s[ 0 ] == 5 );
    assert( s[ 1 ] == 5 );
    assert( *s.raw_begin() == 0b110011 );

    return 0;
}
