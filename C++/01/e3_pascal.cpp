#include <vector>
#include <cassert>
#include <iostream>

/* Write a function which builds the ‹n›-th row of Pascal's triangle
 * as a vector of integers and returns it. */

std::vector< int > pascal( int n ) {
    std::vector<int> result = { 1 };
    for (int i = 1; i <= (n-1); i++)
    {
        int value = (result.back() * ((n-1) - i + 1)) / i;
        result.push_back(value);
    }
    return result;
}

int main()
{
    std::vector< int > p_1 = { 1 },
            p_2 = { 1, 1 },
            p_3 = { 1, 2, 1 },
            p_4 = { 1, 3, 3, 1 },
            p_5 = { 1, 4, 6, 4, 1 },
            p_6 = { 1, 5, 10, 10, 5, 1 };

    assert( pascal( 1 ) == p_1 );
    assert( pascal( 2 ) == p_2 );
    assert( pascal( 3 ) == p_3 );
    assert( pascal( 4 ) == p_4 );
    assert( pascal( 5 ) == p_5 );
    assert( pascal( 6 ) == p_6 );
}
