/* In this exercise, the goal will be to implement a class template
 * which will allow us to iterate over a sequence of number-like
 * objects. */

#include <cassert>
#include <vector>


/* The ‹seq› class should be constructible from 2 number-like
 * objects: the initial value (included) and the final value
 * (excluded). Use pre-increment (operator ‹++›) and equality
 * (operator ‹==›) to generate the values. The dereference operator
 * should return the generated objects by value. */

template< typename T >
class seq_iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
private:
    pointer ptr;
public:
    explicit seq_iterator(pointer ptr) : ptr(ptr) {};
    seq_iterator &operator++() {
        ptr++;
        return *this;
    }
    reference operator*() {
        return *ptr;
    }
    bool operator!=(const seq_iterator<T>& other) {
        return ptr != other.ptr;
    }
}; /* ref: 10 lines */

template< typename T >
class seq {
    std::vector<T> _seq;
    friend seq_iterator<T>;
public:
    seq(T init_value,T final_value) {
        while (!(init_value == final_value)) {
            _seq.emplace_back(init_value);
            ++init_value;
        }
    }

    seq_iterator<T> begin() {
        return seq_iterator<T>(&_seq[0]);
    }

    seq_iterator<T> end() {
        return seq_iterator<T>(&_seq[_seq.size()]);
    }
}; /* ref: 9 lines */

/* A ‹nat› implementation for testing purposes. */

struct nat
{
    int v;
    nat( int v ) : v( v ) {}
    bool operator==( nat o ) const { return v == o.v; }
    nat &operator++() { ++v; return *this; }
};

int main()
{
    int i = 1;
    for ( int j : seq( 1, 10 ) )
        assert( j == i++ );
    assert( i == 10 );

    i = 0;
    for ( double x : seq( 0.2, 2.2 ) )
        switch ( i++ )
        {
            case 0: assert( x == 0.2 ); break;
            case 1: assert( x == 1.2 ); break;
            case 2: assert( x == 2.2 ); break;
            default: assert( false );
        }

    i = 1;
    for ( nat j : seq( nat( 1 ), nat( 10 ) ) )
        assert( j.v == i++ );
    assert( i == 10 );
}
