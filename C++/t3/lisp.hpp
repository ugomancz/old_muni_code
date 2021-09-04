/* In this task, you will implement a simple programming language
 * interpreter: the syntax and semantics will be based on LISP. For
 * simplicity, the only data types will be numbers, symbols and cons
 * cells. */

#include <string_view>
#include <string>
#include <variant>
#include <memory>

/* Accept a string that corresponds to the ‹number› non-terminal as
 * defined below. Store the integer part of the input in ‹value› and
 * return the number of characters processed (including the
 * discarded decimal part). If the input is invalid, return 0. */

int from_string( std::string_view s, int &value );

/* The interpreter itself. The ‹parse› and ‹eval› methods may be
 * called any number of times on the same instance, in any order,
 * and must not interfere with each other. */

template< typename number_t_ >
struct lisp
{
    struct error_t {}; /* indicates parse or evaluation error */
    struct nil_t {};   /* empty list */
    struct cons_t;     /* list cell */
    struct lambda_t;   /* lexical closure */

    using number_t = number_t_;
    using symbol_t = std::string;
    using value_t  = std::variant< number_t, symbol_t, error_t,
                                   cons_t, nil_t, lambda_t >;

    /* Cons (list) cells are the basic building block of LISP
     * programs. A list is built by putting values in ‹car›'s and
     * the successive tails of the list in ‹cdr›'s. The last ‹cdr›
     * of a proper list is always ‹nil_t›. */

    struct cons_t
    {
        std::shared_ptr< value_t > car, cdr;
    };

    /* Syntax:
     *
     *     expr   = { space }, ( atom | list ), { space } ;
     *     list   = '(', expr, { space, expr }, ')' ;
     *     space  = ' ' | ? newline ? ;
     *     atom   = symbol | number ;
     *
     *     number = [ sign ], digits, [ '.', digits ] ;
     *     symbol = s_init, { s_cont } | sign ;
     *
     *     digit  = '0' | '1' | '2' | '3' | '4' |
     *              '5' | '6' | '7' | '8' | '9' ;
     *     sign   = '+' | '-' ;
     *     digits = digit, { digit } ;
     *
     *     s_init = s_char | s_symb ;
     *     s_char = ? alphabetic character ? ;
     *     s_symb = '!' | '$' | '%' | '&' | '*' | '/' | ':' | '<' |
     *              '=' | '>' | '?' | '_' | '~' ;
     *     s_cont = s_init | digit | s_spec ;
     *     s_spec = '+' | '-' | '.' | '@' | '#' ;
     *
     * If the input string does not conform to the above grammar,
     * return a value of type ‹error_t›. Otherwise, the result is
     * one of ‹number_t›, ‹symbol_t›, ‹cons_t› or ‹nil_t›. A ‹list›
     * non-terminal is always parsed as a proper list or a ‹nil_t›.
     *
     * Assume that if you have ‹number_t n›, it is possible to call
     * ‹from_string( "…", n )› with the above semantics (possibly
     * extended to also handle the decimal part). */

    value_t parse( std::string_view expr );

    /* Semantics:
     *
     *  • numbers, nils and lambdas evaluate to themselves,
     *  • symbols evaluate to:
     *    ◦ their bound value in the current lexical environment,
     *    ◦ ‹error_t› if they are unbound,
     *  • lists are evaluated in 3 modes:
     *    ◦ ‹()› to a ‹nil_t›,
     *    ◦ as the ‹if›, ‹let› or ‹lambda› special form,
     *    ◦ as a closure invocations ‹(symbol arg₁ … argₙ)›.
     *
     * Special forms:
     *
     *  • ‹(if cond expr₁ expr₂)›:
     *    ◦ evaluate to ‹expr₁› if ‹cond› evaluates to non-zero,
     *    ◦ evaluate to ‹expr₂› if ‹cond› evaluates to zero,
     *    ◦ evaluate to ‹error› otherwise,
     *  • ‹(let (name value) expr)›: evaluate to ‹expr›, in a
     *    lexical environment in which ‹name› is bound to ‹value›
     *    recursively (i.e. if ‹value› is a lambda, it may call
     *    itself using ‹name›),
     *  • ‹(lambda list expr)› evaluates to ‹lambda_t› (an anonymous
     *    closure) with names of formal arguments given by ‹list›.
     *
     * Closure invocation:
     *
     *  • the symbol in the ‹car› position of the list must evaluate
     *    to a ‹lambda_t› (the result is ‹error_t› otherwise),
     *  • the entire list then evaluates the body of the lambda
     *    in the lexical environment in which the closure was
     *    defined,
     *  • extended by binding each formal argument to the
     *    corresponding ‹argₙ›, evaluated in the «current» lexical
     *    environment;
     *  • if the number of actual arguments does not match the
     *    number of formal arguments, the entire list evaluates
     *    to ‹error›.
     *
     * The top-level lexical environment is empty with the exception
     * of following «builtin functions»:
     *
     *  • ‹+›, ‹-›, ‹*›, ‹/› which each accepts exactly 2 operands
     *    of type ‹number_t› and evaluates to the obvious thing,
     *  • ‹car› and ‹cdr› which expect exactly one value of type
     *    ‹cons_t› and evaluate to its ‹car› or ‹cdr› part,
     *  • ‹cons› which accepts exactly 2 arguments and constructs a
     *    list cell out of them,
     *  • ‹list› which accepts arbitrary arguments and returns a
     *    cons list of all of them.
     *
     * Anything not covered above evaluates to ‹error_t›. */

    value_t eval( value_t expr );
};
