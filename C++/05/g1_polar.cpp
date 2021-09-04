/* The first thing we will do is implement a simple class which
 * represents complex numbers using their polar form. This form
 * makes multiplication and division easier, so that is what we will
 * do here (see also ‹cartesian.cpp› for definition of addition).
 *
 *  • the constructor takes the modulus and the argument (angle)
 *  • add ‹abs› and ‹arg› methods to access the attributes
 *  • implement multiplication and division on ‹polar›
 *  • implement equality for ‹polar›; keep in mind that if the
 *    modulus is zero, the argument (angle) is irrelevant
 *
 * NB. The argument is «periodic»: either normalize it to fall
 * within [0, 2π), or otherwise make sure that ‹polar( 1, x ) ==
 * polar( 1, x + 2π )›. The equality operator you implement should
 * be tolerant of imprecision: use ‹std::fabs( x - y ) < 1e-10›
 * instead of ‹x == y› when dealing with real numbers.
 */

#include <cmath>
#include <cassert>

class polar {
    double mod, arg;

    void normalize() {
        while (arg < 0) {
            arg += 2 * (std::atan(1) * 4);
        }
        arg = std::fmod(arg, (std::atan(1) * 4));
    }

public:
    polar(double modulus, double argument) : mod(modulus), arg(argument) {
        normalize();
    }

    friend polar operator*(const polar &left, const polar &right) {
        auto copy = left;
        copy.mod *= right.mod;
        copy.arg += right.arg;
        copy.normalize();
        return copy;
    }

    friend polar operator/(const polar &left, const polar &right) {
        auto copy = left;
        copy.mod /= right.mod;
        copy.arg -= right.arg;
        copy.normalize();
        return copy;
    }

    friend bool operator==(const polar &left, const polar &right) {
        if (left.mod == 0 && right.mod == 0) {
            return true;
        }
        return (std::fabs(left.mod - right.mod) < 1e-10) && (std::fabs(left.arg - right.arg) < 1e-10);
    }
}; /* reference implementation: 29 lines */

int main()
{
    polar zero( 0, 0 ), one( 1, 0 ), i( 1, 2 * std::atan( 1 ) );
    polar minus_one( 1, 4 * std::atan( 1 ) );

    assert( zero * one == zero );
    assert( zero * i == zero );
    assert( one * i == i );
    assert( i * i == minus_one );
    assert( i / i == one );
    assert( one / i == minus_one * i );
    assert( minus_one * minus_one == one );
    assert( minus_one / minus_one == one );
}
