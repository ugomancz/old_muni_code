class component
{
    int left_i, right_i;
    component *left = nullptr,
              *right = nullptr;

protected:
    virtual bool eval_0( bool, bool ) { return false; }
    virtual bool eval_1( bool, bool ) { return false; }

    bool get_left() const { return left ? left->read( left_i ) : false; }
    bool get_right() const { return right ? right->read( right_i ) : false; }

public:
    void connect( int i, int o, component &c )
    {
        ( i ? right_i : left_i ) = o;
        ( i ? right : left ) = &c;
    }

    virtual bool read( int o )
    {
        auto l = get_left();
        auto r = get_right();
        if ( o == 0)
            return eval_0( l, r );
        else
            return eval_1( l, r );
    }

    virtual ~component() = default;
};

class cnot : public component
{
    bool eval_0( bool x, bool ) override { return x; }
    bool eval_1( bool x, bool y ) override
    {
        if ( x )
            return y;
        else
            return !y;
    }
};

class nand : public component
{
    bool eval_0( bool x, bool y ) override { return !( x && y ); }
    bool eval_1( bool x, bool y ) override { return x && y; }
};

class eq : public component
{
    bool eval_0( bool x, bool y ) override { return x == y; }
    bool eval_1( bool x, bool y ) override { return x != y; }
};

class delay : public component
{
    bool _x = false, _y = false;
    bool _in_read = false;

    bool read( int o ) override
    {
        bool out = o ? _y : _x;

        if ( _in_read )
            return out;

        _in_read =true;
        _x = get_left();
        _y = get_right();
        _in_read = false;

        return out;
    }
};

class latch : public component
{
    bool _value = false;

    bool eval_0( bool x, bool y ) override { return  eval( x, y ); }
    bool eval_1( bool x, bool y ) override { return !eval( x, y ); }

    bool eval( bool x, bool y )
    {
        if ( !x && y ) _value = true;
        if ( x ) _value = false;

        return _value;
    }
};

#include "f3_loops.cpp"
