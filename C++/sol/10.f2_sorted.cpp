#include <any>

struct check_sorted
{
    std::any last;
    bool mismatch = false;

    bool was_sorted() const { return !mismatch; }

    template< typename value_t >
    void operator()( const value_t &v )
    {
        if ( last.has_value() )
        {
            if ( std::any_cast< value_t >( last ) > v )
                mismatch = true;
        }

        last = v;
    }
};

#include "f2_sorted.cpp"
