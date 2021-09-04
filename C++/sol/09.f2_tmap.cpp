#include <type_traits>
#include <vector>

template< typename value_t >
struct tree;

template< typename fun_t, typename val_t >
using mapped_tree = tree< std::invoke_result_t< fun_t, val_t > >;

template< typename fun_t, typename val_t >
using mapped_vec =
    std::vector< std::invoke_result_t< fun_t, val_t > >;

template< typename fun_t, typename value_t >
mapped_tree< fun_t, value_t >
tmap( fun_t f, const tree< value_t > &t );

#include "f2_tmap.cpp"

template< typename fun_t, typename value_t >
auto map( fun_t f, const std::vector< value_t > &vec )
{
    mapped_vec< fun_t, value_t > out;
    for ( const auto &v : vec )
        out.push_back( f( v ) );
    return out;
}

template< typename fun_t, typename value_t >
mapped_tree< fun_t, value_t >
tmap( fun_t f, const tree< value_t > &t )
{
    using mt = mapped_tree< fun_t, value_t >;

    auto map_sub = [&]( const auto &subtree )
    {
        return tmap( f, subtree );
    };

    return mt( f( t.value ), map( map_sub, t.children ) );
}
