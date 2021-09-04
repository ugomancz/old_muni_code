#include <algorithm>
#include <memory>

template< typename container_t >
class range
{
    using data_ptr = std::shared_ptr< container_t >;
    using iterator = typename container_t::const_iterator;
    data_ptr _data;
    iterator _b, _e;

public:
    range( container_t c )
        : _data( std::make_shared< container_t >( std::move( c ) ) ),
          _b( _data->begin() ), _e( _data->end() )
    {}

    range( data_ptr c, iterator b, iterator e )
        : _data( c ), _b( b ), _e( e )
    {}

    auto begin() const { return _b; }
    auto end()   const { return _e; }

    range take( int n ) const
    {
        return { _data, _b, std::next( _b, n ) };
    }

    range drop( int n ) const
    {
        return { _data, std::next( _b, n ), _e };
    }

    template< typename C >
    friend bool operator==( range a, range< C > b )
    {
        return std::equal( a.begin(), a.end(), b.begin(), b.end() );
    }
};

#include "f2_range.cpp"
