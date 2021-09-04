struct null;

template< typename cdr_t >
struct cons
{
    int car;
    cdr_t cdr;
    cons( int car, const cdr_t &cdr ) : car( car ), cdr( cdr ) {}
};

int sum( null );

template< typename cons_t >
int sum( const cons_t & c )
{
    return c.car + sum( c.cdr );
}

#include "f1_icons.cpp"

int sum( null )
{
    return 0;
}
