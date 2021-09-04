/* In this exercise, we will represent rational numbers (fractions)
 * with addition and ordering. The constructor of ‹rat› should take
 * the numerator and the denominator (in this order), which are both
 * integers. It should be possible to compare ‹rat› instances for
 * equality and inequality (in this exercise, it is enough to
 * implement the less-than operator , i.e. ‹a < b›).
 *
 * NB. Recall how fractions with different denominators are
 * compared (and added). Your implementation does not need to be
 * very efficient, or work for very large numbers. */

#include <cassert>
#include <numeric>

class rat {
private:
    int num, denom;

    void normalize() {
        int divisor = std::gcd(num, denom);
        num /= divisor;
        denom /= divisor;
    }

public:
    rat(int numerator, int denominator) : num(numerator), denom(denominator) {
        normalize();
    }

    friend bool operator<(const rat &left, const rat &right) {
        /* lowest common multiple */
        int lcm = (left.denom * right.denom) / std::gcd(left.denom, right.denom);
        return lcm / left.denom * left.num < lcm / right.denom * right.num;
    }

    friend rat operator+(const rat &left, const rat &right) {
        auto copy = left;
        int lcm = (copy.denom * right.denom) / std::gcd(copy.denom, right.denom);
        copy.num = lcm / copy.denom * copy.num + lcm / right.denom * right.num;
        copy.denom = lcm;
        copy.normalize();
        return copy;
    }

    bool operator==(const rat &right) const {
        return num == right.num && denom == right.denom;
    }
}; /* reference implementation: 9 lines */

int main()
{
    rat one( 1, 1 ), half( 1, 2 ), three_halves( 3, 2 ),
        minus_half( -1, 2 ), third( 1, 3 ), two( 2, 1 ),
        minus_sixth( -1, 6 );

    assert( half < one );
    assert( one < three_halves );
    assert( half < three_halves );

    assert( half + half == one );
    assert( half + one == three_halves );
    assert( one < one + one );
    assert( minus_half + minus_half < minus_half );
    assert( minus_half < half );
    assert( three_halves + minus_half == one );
    assert( half + third < one );
    assert( minus_half < minus_sixth );
    assert( minus_half + third == minus_sixth );
}
