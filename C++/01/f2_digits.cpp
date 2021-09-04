#include <vector>
#include <cassert>
#include <algorithm>

std::vector<int> digits(int n, int base) {
    std::vector<int> result;
    do {
        result.push_back(n%base);
        n /= base;
    } while (n > 0);
    std::reverse(result.begin(), result.end());
    return result;
}

int main()
{
    std::vector< int > d10_1337 = { 1, 3, 3, 7 },
                       d10_123  = { 1, 2, 3 },
                       d7_1234  = { 3, 4, 1, 2 },
                       d2_9     = { 1, 0, 0, 1 };
    assert( digits( 1337, 10 ) == d10_1337 );
    assert( digits( 123,  10 ) == d10_123 );
    assert( digits( 1234,  7 ) == d7_1234 );
    assert( digits( 9, 2 ) == d2_9 );
}
