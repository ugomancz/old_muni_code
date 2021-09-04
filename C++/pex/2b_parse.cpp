/* This task is worth «10 points». */

/* Implement a parser for a simple language, which has atoms (single
 * alphabetic character) and lists, written using parentheses around
 * space-delimited elements (which can be either atoms or lists). A
 * few examples of valid inputs:
 *
 *  • x
 *  • (x)
 *  • (x y)
 *  • (x (x y))
 *
 * And so on and so forth. Write a single function ‹parse› which
 * accepts an ‹std::string›, with the following properties:
 *
 *  • the function throws an exception iff the input is ill-formed
 *  • the return value is an object specified below
 *
 * The object returned by ‹parse› should provide the following
 * interface (all methods are ‹const›):
 *
 *  • ‹is_list› which returns a boolean,
 *  • ‹items› which returns an object which can be iterated
 *    (UB if ‹is_list› is false),
 *  • ‹name› which returns a ‹char› (UB if ‹is_list› is true).
 *
 *  Dereferencing an iterator which belongs to the object returned
 *  by ‹items› should yield another object with the interface above.
 *
 * The formal grammar, in EBNF:
 *
 *    item    = atom | list;
 *    list    = '(', items, ')' | '()' ;
 *    items   = { item, ' ' }, item ;
 *    atom    = ? character x iff std::isalpha( x ) ? ;
 */

#include <cassert>
#include <string>

/* What follows are «basic» test cases for your convenience. You can
 * add additional test cases into main(): they will be «not»
 * executed during evaluation, so it is okay to submit with broken
 * main. However, make sure to «not» alter the prototype. */

int main()
{
    auto check_throws = []( std::string s )
    {
        try
        {
            parse( s );
            assert( false );
        }
        catch ( ... ) {}
    };

    check_throws( "(xy)" );
    check_throws( "(" );
    check_throws( ")" );
    check_throws( "1" );
    check_throws( "( )" );
    check_throws( "( x )" );
    check_throws( "(x )" );
    check_throws( "( x)" );
    check_throws( "(x  y)" );

    parse( "()" );
    parse( "(x y)" );

    assert( parse( "()" ).is_list() );
    assert( parse( "(x)" ).is_list() );

    const auto &&parsed = parse( "(x)" );
    for ( const auto &i : parsed.items() )
    {
        assert( !i.is_list() );
        assert( i.name() == 'x' );
    }

    return 0;
}
