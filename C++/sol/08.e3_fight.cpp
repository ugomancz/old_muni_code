class rock;
class paper;
class scissors;

class gesture
{
public:
    virtual bool visit( const rock & ) const = 0;
    virtual bool visit( const paper & ) const = 0;
    virtual bool visit( const scissors & ) const = 0;
    virtual bool fight( const gesture & ) const = 0;
};

class rock : public gesture
{
    bool visit( const rock & )     const override { return false; }
    bool visit( const paper & )    const override { return true;  }
    bool visit( const scissors & ) const override { return false; }

    bool fight( const gesture &g ) const override
    {
        return g.visit( *this );
    }
};

class paper : public gesture
{
    bool visit( const rock & )     const override { return false; }
    bool visit( const paper & )    const override { return false; }
    bool visit( const scissors & ) const override { return true;  }

    bool fight( const gesture &g ) const override
    {
        return g.visit( *this );
    }
};

class scissors : public gesture
{
    bool visit( const rock & )     const override { return true; }
    bool visit( const paper & )    const override { return false; }
    bool visit( const scissors & ) const override { return false; }

    bool fight( const gesture &g ) const override
    {
        return g.visit( *this );
    }
};

#include "e3_fight.cpp"
