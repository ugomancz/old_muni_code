struct tristate
{
    bool val, det;
};

const tristate yes  { true,  true };
const tristate no   { false, true };
const tristate maybe{ false, false };

tristate operator&&( tristate a, tristate b )
{
    if ( a.det && b.det )
        return a.val && b.val ? yes : no;
    if ( ( a.det && !a.val ) || ( b.det && !b.val ) )
        return no;
    else
        return maybe;
}

tristate operator||( tristate a, tristate b )
{
    if ( a.det && b.det )
        return a.val || b.val ? yes : no;
    if ( ( a.det && a.val ) || ( b.det && b.val ) )
        return yes;
    else
        return maybe;
}

bool operator==( tristate a, tristate b )
{
    if ( a.det && b.det )
        return a.val == b.val;
    else
        return a.det == b.det;
}

#include "e3_ternary.cpp"
