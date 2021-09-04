#include <vector>
#include <variant>

template< typename seq1_t, typename seq2_t >
auto select( const seq1_t &s1, const seq2_t &s2,
             const std::vector< bool > &bmp )
{
    using variant = std::variant< typename seq1_t::value_type,
                                  typename seq2_t::value_type >;
    std::vector< variant > out;

    auto i = s1.begin();
    auto j = s2.begin();

    for ( bool first : bmp )
    {
        out.emplace_back( first ? variant( *i ) : variant( *j ) );
        ++ i, ++ j;
    }

    return out;
}

#include "e3_select.cpp"
