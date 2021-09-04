#include <vector>
#include <cassert>

/* Write a map function, which takes a function ‹f› and a vector ‹v› and
 * returns a new vector ‹w› such that w[ i ] = f( v[ i ] ) for any valid index
 * ‹i›. We will need to use the ‘lambda’ syntax for this, since we don't yet
 * know any other way to write functions which accept functions as arguments. */

/** zadání negarantovalo, že vektor musí být nutně vektor intů **/
static auto map = [](auto f, const std::vector<int> &vector) {
    std::vector<int> result;
    for (const int &number : vector) {
        result.emplace_back(f(number));
    }
    return result;
};

/* Similar, but ‹f› is a binary function, and there are two input vectors of
 * equal length. You do not need to check this. */

static auto zip = [](auto f, const std::vector<int> &vector1, const std::vector<int> &vector2) {
    std::vector<int> result;
    for (size_t i = 0; i < vector1.size(); i++) {
        result.emplace_back(f(vector1.at(i), vector2.at(i)));
    }
    return result;
};

/* You can assume that the output vector is of the same type as the input
 * vector (i.e. ‹f› is of type a → a in map, and of type a → b → a for ‹zip›. */

int main()
{
    using intv = std::vector< int >;

    intv a{ 1, 2, 3, 4, 5 };

    intv b = map( []( int x ) { return 2 * x; }, a );
    intv c = map( []( int x ) { return x * x; }, a );
    intv d = zip( []( int x, int y ) { return x * y; }, a, a );

    assert( b == ( intv{ 2, 4, 6, 8, 10 } ) );
    assert( c == ( intv{ 1, 4, 9, 16, 25 } ) );
    assert( d == ( intv{ 1, 4, 9, 16, 25 } ) );
}
