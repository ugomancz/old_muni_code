class token
{
    bool valid = false;
    friend class machine;

public:
    token() = default;
    token( const token & ) = delete;
    token( token &&o ) : valid( o.valid )
    {
        o.valid = false;
    }

    token &operator=( const token & ) = delete;
    token &operator=( token &&o ) noexcept
    {
        valid = o.valid;
        o.valid = false;
        return *this;
    }
};

class machine
{
    bool busy = false;
public:
    token make();
    void fetch( token &t );
};

#include "e3_coffee.cpp"

token machine::make()
{
    if ( busy )
        throw ::busy();
    token t;
    t.valid = true;
    busy = true;
    return t;
}

void machine::fetch( token &t )
{
    assert( busy );

    if ( !t.valid )
        throw invalid();

    t.valid = false;
}
