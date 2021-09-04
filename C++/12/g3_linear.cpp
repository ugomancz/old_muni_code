/* Remember the linear equation solver from ‹08/linear.cpp›? Let's
 * do that again, but this time with a simple parser instead of
 * operator overloading. */

#include <cassert>
#include <cmath>
#include <utility>
#include <string>

/* Write a function ‹solve› which takes a string as its input, and
 * returns an ‹std::pair› of floating point numbers. The input
 * contains 2 linear equations, one per line, with 2 single-letter
 * alphabetic variables and integer coefficients. The result should
 * be ordered alphabetically (e.g. x, y). */

std::pair< double, double > solve( const std::string &eq );

/* ref: solve 26 lines, helper class 19 lines */

int main()
{
    std::pair a( 1.0, 0.0 ), b( -1.0, 0.0 ), c( .6, -.2 );

    assert( solve( " x + y     =  1\n x -  y     =  1" ) == a );
    assert( solve( " x + y     = -1\n x -  y     = -1" ) == b );
    assert( solve( " x + y     =  x\n x +  y     =  1" ) == a );
    assert( solve( "2x + y     =  1\n x - 2y     =  1" ) == c );
    assert( solve( " x + y - 1 =  0\n x -  y - 1 =  0" ) == a );
    assert( solve( "10x + 10y  = 10\n x -  y     =  1" ) == a );
}
