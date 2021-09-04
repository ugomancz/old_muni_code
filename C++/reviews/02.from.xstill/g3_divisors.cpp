#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

/* Take a number, find all its «prime» divisors and add them into
 * ‹divs›, unless they are already there. Be sure to do this in time
 * proportional (linear) to the input number.
 *
 * «Bonus»: If you assume that ‹divs› is sorted in ascending order
 * when you get it, you can make ‹add_divisors› a fair bit more
 * efficient. Can you figure out how? */

void add_divisors(int num, std::vector<int> &divs) {
    /** duplikace kódu – 2 není nijak speciální a dá se vyřešit spolu s dalšími
     ** čísly **/
    while (num % 2 == 0) {
        /** použití std::find je fajn **/
        if (std::find(divs.begin(), divs.end(), 2) == divs.end()) {
            divs.emplace_back(2);
        }
        num /= 2;
    }
    for (int i = 3; i <= std::sqrt(num); i += 2) {
        while (num % i == 0) {
            if (std::find(divs.begin(), divs.end(), i) == divs.end()) {
                divs.emplace_back(i);
            }
            num /= i;
        }
    }
    if (num > 2 and std::find(divs.begin(), divs.end(), num) == divs.end()) {
        divs.emplace_back(num);
    }
}

int main()
{
    std::vector< int > divs;

    add_divisors( 7, divs );
    assert( divs.size() == 1 );
    assert( divs[ 0 ] == 7 );

    add_divisors( 14, divs );
    std::sort( divs.begin(), divs.end() );
    assert( divs.size() == 2 );
    assert( divs[ 0 ] == 2 );
    assert( divs[ 1 ] == 7 );

    add_divisors( 32, divs );
    std::sort( divs.begin(), divs.end() );
    assert( divs.size() == 2 );
    assert( divs[ 0 ] == 2 );
    assert( divs[ 1 ] == 7 );

    add_divisors( 18, divs );
    std::sort( divs.begin(), divs.end() );
    assert( divs.size() == 3 );
    assert( divs[ 0 ] == 2 );
    assert( divs[ 1 ] == 3 );
    assert( divs[ 2 ] == 7 );
}
