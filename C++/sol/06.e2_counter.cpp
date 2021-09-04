struct counted
{
    counted();
    counted( const counted & );
    ~counted();
};

#include "e2_counter.cpp"

counted::counted()
{
    ++ counter;
}

counted::counted( const counted & )
{
    ++ counter;
}

counted::~counted()
{
    -- counter;
}
