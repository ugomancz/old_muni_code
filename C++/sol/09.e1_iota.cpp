template< typename fun_t >
void iota( fun_t f, int start, int end )
{
    for ( int i = start; i < end; ++ i )
        f( i );
}

#include "e1_iota.cpp"
