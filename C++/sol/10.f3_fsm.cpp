#include <string_view>
#include <map>

template< typename letter_t >
class fsm
{
    std::map< letter_t, const fsm * > _next;
    bool _accept;

public:
    explicit fsm( bool a = false ) : _accept( a ) {}
    void next( letter_t c, const fsm &n ) { _next[ c ] = &n; }

    template< typename seq_t >
    bool accept( const seq_t &s ) const
    {
        return accept( s.begin(), s.end() );
    }

    template< typename iter_t >
    bool accept( iter_t b, iter_t e ) const
    {
        if ( b == e ) return _accept;

        if ( auto n = _next.find( *b ); n != _next.end() )
            return n->second->accept( ++b, e );
        else
            return false;
    }
};

#include "f3_fsm.cpp"
