#include <vector>

using intvec = std::vector< int >;

intvec::iterator bsearch( intvec &vec, int val )
{
    auto b = vec.begin(), e = vec.end();

    while ( b < e ) /* the search interval is not empty */
    {
        auto mid = b + ( e - b ) / 2;
        if ( val < *mid ) e = mid;     /* must be in [b, mid) */
        if ( val > *mid ) b = mid + 1; /* must be in (mid, e) */
        if ( val == *mid ) return mid; /* we found it */
    }

    return vec.end();
}

#include "f4_bsearch.cpp"
