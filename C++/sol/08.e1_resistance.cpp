class segment
{
public:
    virtual double r() const = 0;
};

class series : public segment
{
    double total = 0;
public:
    void add( double r ) { total += r; }
    void add( const segment &s ) { total += s.r(); }
    double r() const override { return total; }
};

class parallel : public segment
{
    double recip = 0;
public:
    void add( double r ) { recip += 1.0 / r; }
    void add( const segment &s ) { recip += 1.0 / s.r(); }
    double r() const override { return 1.0 / recip; }
};

double resistance( const segment &s )
{
    return s.r();
}

#include "e1_resistance.cpp"
