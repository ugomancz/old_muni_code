#include <memory>
#include <algorithm>

class dynarray
{
    std::unique_ptr< int[] > _data;
    int _size;
public:

    dynarray( int size )
        : _data( std::make_unique< int[] >( size ) ),
          _size( size )
    {}

    void resize( int size )
    {
        auto d_new = std::make_unique< int[] >( size );
        auto d_old = _data.get();
        std::copy( d_old, d_old + std::min( size, _size ),
                   d_new.get() );
        _data = std::move( d_new );
        _size = size;
    }

    int &operator[]( int i )
    {
        return _data[ i ];
    }
};

#include "e1_dynarray.cpp"
