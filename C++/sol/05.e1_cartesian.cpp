/* This is a solution that uses the friend syntax. For a solution
 * which uses the method syntax, see ‹complex.alt.cpp›. */

class complex
{
    double real, imag;
public:
    complex( double r, double i ) : real( r ), imag( i ) {}

    friend complex operator+( complex a, complex b )
    {
        /* You may not know this syntax yet. In a return statement,
         * braces without a type name call the constructor of the
         * return type. I.e. ‹{ a, b }› in this context is the same
         * as ‹complex( a, b )›. */

        return { a.real + b.real, a.imag + b.imag };
    }

    friend complex operator-( complex a, complex b )
    {
        return { a.real - b.real, a.imag - b.imag };
    }

    friend complex operator-( complex a )
    {
        return { -a.real, -a.imag };
    }

    friend bool operator==( complex a, complex b )
    {
        return a.real == b.real && a.imag == b.imag;
    }
};

/* To avoid having a copy of the tests, we ‹#include› the original
 * ‹.cpp› file here. You won't be able to compile this solution if
 * you add your implementation to the original ‹.cpp› file, but you
 * can probably trust us that the solution above works. */

#include "e1_cartesian.cpp"
