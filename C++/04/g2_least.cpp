#include <cassert>
#include <memory>
#include <vector>
#include <algorithm>

/* The class ‹element› represents a value which, for whatever
 * reason, cannot be duplicated. Our goal will be to write a
 * function which takes a vector of these, finds the smallest and
 * returns it. Do not change the definition of ‹element› in any
 * way. */

class element
{
    int value;
public:
    element( int v ) : value( v ) {}
    element( element &&v ) : value( v.value ) {}
    element &operator=( element &&v ) = default;
    bool less_than( const element &o ) const { return value < o.value; }
    bool equal( const element &o ) const { return value == o.value; }
};

using data = std::vector< element >;

/* Write function ‹least› (or a couple of function overloads) so
 * that calling ‹least( d )› where ‹d› is of type ‹data› returns the
 * least element in the input vector. */

const element &least(const data &d) {
    auto smallest_index = d.size() - 1;
    for (int i = 0; i < static_cast<int>(d.size()); i++) {
        if (d.at(i).less_than(d.at(smallest_index))) {
            smallest_index = i;
        }
    }
    return d.at(smallest_index);
}

element least(data &&d) {
    auto smallest_index = d.size() - 1;
    for (int i = 0; i < static_cast<int>(d.size()); i++) {
        if (d.at(i).less_than(d.at(smallest_index))) {
            smallest_index = i;
        }
    }
    return std::move(d.at(smallest_index));
}

int main()
{
    auto mk = []( auto... vs )
    {
        data d;
        ( d.emplace_back( vs ), ... );
        return d;
    };

    data d_1 = mk( 1, 2, 3 ), d_2 = mk( 3, 2, 7 );
    assert( least( d_1 ).equal( 1 ) );
    assert( least( d_2 ).equal( 2 ) );
    const element &l = least( mk( 4, 3, 1, 2 ) );
    assert( l.equal( 1 ) );
}
