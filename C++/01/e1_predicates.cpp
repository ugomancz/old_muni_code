#include <vector>
#include <cassert>

/* Write the following predicates (pure functions which return a
 * boolean value). The first two return true if all (‹all_odd›) or
 * at least one (‹any_odd›) number in the list is odd: */

bool all_odd( const std::vector< int > & in) {
    bool flag = true;
    for (const int &number : in) {
        flag = flag and (number % 2 != 0);
    }
    return flag;
}
bool any_odd( const std::vector< int > & in) {
    bool flag = false;
    for (const int &number : in) {
        flag = flag or (number % 2 != 0);
    }
    return flag;
}

/* The third returns true if there are at least ‹n› numbers
 * divisible by ‹k›: */

bool count_divisible( const std::vector< int > & input, int k, int n ) {
    short count = 0;
    for (const int &number : input) {
        if (number % k == 0) {
            count++;
        }
    }
    return (count >= n);
}

int main()
{
    std::vector< int > odd{ 1, 3, 5, 7, 13 };
    std::vector< int > mostly_odd{ 1, 3, 5, 6, 7, 13 };
    std::vector< int > even{ 2, 4, 8, 10 };
    std::vector< int > m7{ 14, 28, 42, 56 };

    assert(  all_odd( odd ) );
    assert( !all_odd( mostly_odd ) );
    assert(  any_odd( odd ) );
    assert(  any_odd( mostly_odd ) );
    assert( !any_odd( even ) );
    assert(  count_divisible( even, 2, 3 ) );
    assert(  count_divisible( even, 2, 4 ) );
    assert( !count_divisible( even, 2, 5 ) );
    assert(  count_divisible( m7,   7, 4 ) );
    assert(  count_divisible( m7,   2, 4 ) );
}
