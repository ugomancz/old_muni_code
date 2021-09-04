template< typename iter_t >
class skip
{
    iter_t _begin, _end;
    int _skip;
public:

    struct iterator
    {
        iter_t iter, end;
        int skip;

        decltype( auto ) operator*()       { return *iter; }
        decltype( auto ) operator*() const { return *iter; }

        bool operator==( iterator o ) const
        {
            return iter == o.iter;
        }

        bool operator!=( iterator o ) const
        {
            return iter != o.iter;
        }

        iterator operator++( int )
        {
            iterator i = *this;
            ++*this;
            return i;
        }

        iterator &operator++()
        {
            for ( int i = 0; i < skip; ++ i )
                if ( iter != end )
                    ++iter;
            return *this;
        }
    };

    skip( iter_t b, iter_t e, int s )
        : _begin( b ), _end( e ), _skip( s )
    {}

    iterator begin() const { return { _begin, _end, _skip }; }
    iterator end()   const { return { _end,   _end, _skip }; }
};

#include "e3_skip.cpp"
