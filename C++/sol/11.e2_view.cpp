template< typename iter_t >
class view
{
    iter_t _begin, _end;
public:
    view( iter_t b, iter_t e ) : _begin( b ), _end( e ) {}
    iter_t begin() const { return _begin; }
    iter_t end()   const { return _end; }
};

#include "e2_view.cpp"
