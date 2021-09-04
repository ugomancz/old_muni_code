#include <vector>
#include <cassert>
#include <functional>
#include <numeric>

/* Write a function ‹accumulate( f, vec )› which will sum up ⟦f(x)⟧
 * for all ⟦x⟧ in the given ‹std::vector< int > vec›. */

// auto accumulate = …

int accumulate(const std::function<int(int)> &f, const std::vector<int> &vector) {
    int result = 0;
    for (const int &value : vector) {
        result += f(value);
    }
    return result;
}

int main()
{
    auto f = []( int x ) { return x * x; };
    auto g = []( int x ) { return x / 2; };
    auto h = []( int x ) { return x; };

    std::vector vec{ 1, 2, 3, 4 };

    assert( accumulate( f, vec ) == 30 );
    assert( accumulate( g, vec ) ==  4 );
    assert( accumulate( h, vec ) == 10 );
}
