#include <memory>

class list
{
    int _head;
    std::unique_ptr< list > _tail;
public:

    list( const list &o )
        : _head( o._head ),
          _tail( o._tail ? std::make_unique< list >( *o._tail )
                         : nullptr )
    {}

    list( int h, const list &t )
        : _head( h ),
          _tail( std::make_unique< list >( t ) )
    {}

    list() = default;

    bool empty() const { return !_tail; }
    int head() const { return _head; }
    const list &tail() const { return *_tail; }
};

#include "e2_list.cpp"
