#include <vector>

template< typename seq1_t, typename seq2_t >
auto concat( const seq1_t &s1, const seq2_t &s2 )
{
    std::vector< typename seq1_t::value_type > out;

    for ( const auto &x : s1 )
        out.push_back( x );
    for ( const auto &x : s2 )
        out.push_back( x );

    return out;
}

#include "e2_concat.cpp"
