template< typename value_t >
struct tree;

template< typename fun_t, typename value_t >
value_t tfold( fun_t f, const tree< value_t > &t );

#include "f1_tfold.cpp"

template< typename fun_t, typename value_t >
value_t tfold( fun_t f, const tree< value_t > &t )
{
    if ( !t.left )
        return t.value;

    auto left  = tfold( f, *t.left ),
         right = tfold( f, *t.right );

    return f( f( t.value, left ), right );
}
