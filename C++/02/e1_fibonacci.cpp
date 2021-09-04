#include <vector>
#include <cassert>
#include <numeric>

/* Fill in an existing vector with a Fibonacci sequence (i.e. after
 * calling ‹fibonacci( v, n )›, the vector ‹v› should contain the
 * first ‹n› Fibonacci numbers, and nothing else). */

void fibonacci(std::vector<int> &vector, const int length) {
    vector.clear();
    int x = 1, y = 1, z = 0;
    vector.emplace_back(x);
    vector.emplace_back(y);
    for (int i = 0; i < length - 2; i++) {
        z = x+y;
        x = y;
        y = z;
        vector.emplace_back(z);
    }
}

int main()
{
    std::vector< int > fib, expect{ 1, 1, 2, 3, 5 };

    fibonacci( fib, 5 );
    assert( fib == expect );

    fibonacci( fib, 6 );
    expect.push_back( 8 );
    assert( fib == expect );

    fib = std::vector< int >{ 4, 5 };
    fibonacci( fib, 6 );
    assert( fib == expect );
}
