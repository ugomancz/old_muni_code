/* Implement binary search on a vector. In this case, we will use a non-const
 * reference to pass the vector, because we don't know yet how to deal with
 * const iterators properly. We also don't know how to write generic algorithms
 * (we will see that at the end of this course), so we use a vector of
 * integers.
 *
 * It is customary to return the «end» iterator if an element is not found. A
 * pair of iterators in C++, by convention, denotes a left-closed / right-open
 * interval, like this: [begin, end). */

#include <vector>
#include <cassert>

std::vector<int>::iterator rec_bsearch(std::vector<int> &vector, int val, int left, int right) {
    if (left <= right) {
        int middle = left + (right - left) / 2;
        if (vector.at(middle) == val) {
            return vector.begin() + middle;
        } else if (vector.at(middle) > val) {
            return rec_bsearch(vector, val, left, middle - 1);
        } else {
            return rec_bsearch(vector, val, middle + 1, right);
        }

    }
    return vector.end();
}

std::vector<int>::iterator bsearch(std::vector<int> &vec, int val) {
    int right = vec.size() - 1;
    int left = 0;
    return rec_bsearch(vec, val, left, right);
}

int main()
{
    using vec = std::vector< int >;
    vec a{ 1, 2, 3, 4, 5 }, b{ 1, 2, 3, 4 }, c{ 1, 3, 7, 9, 51 };

    assert( bsearch( a, 1 ) == std::next( a.begin(), 0 ) );
    assert( bsearch( a, 2 ) == std::next( a.begin(), 1 ) );
    assert( bsearch( a, 3 ) == std::next( a.begin(), 2 ) );
    assert( bsearch( a, 4 ) == std::next( a.begin(), 3 ) );
    assert( bsearch( a, 5 ) == std::next( a.begin(), 4 ) );
    assert( bsearch( a, 0 ) == a.end() );
    assert( bsearch( a, 6 ) == a.end() );

    assert( bsearch( b, 1 ) == std::next( b.begin(), 0 ) );
    assert( bsearch( b, 2 ) == std::next( b.begin(), 1 ) );
    assert( bsearch( b, 3 ) == std::next( b.begin(), 2 ) );
    assert( bsearch( b, 4 ) == std::next( b.begin(), 3 ) );
    assert( bsearch( b, 0 ) == b.end() );
    assert( bsearch( b, 5 ) == b.end() );

    assert( bsearch( c, 1 )  == std::next( c.begin(), 0 ) );
    assert( bsearch( c, 2 )  == c.end() );
    assert( bsearch( c, 3 )  == std::next( c.begin(), 1 ) );
    assert( bsearch( c, 4 )  == c.end() );
    assert( bsearch( c, 5 )  == c.end() );
    assert( bsearch( c, 7 )  == std::next( c.begin(), 2 ) );
    assert( bsearch( c, 9 )  == std::next( c.begin(), 3 ) );
    assert( bsearch( c, 11)  == c.end() );
    assert( bsearch( c, 51 ) == std::next( c.begin(), 4 ) );
    assert( bsearch( c, 0 )  == c.end() );
}
