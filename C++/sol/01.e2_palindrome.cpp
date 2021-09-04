#include "e2_palindrome.cpp"

bool is_palindrome( const std::string &s )
{
    for ( int i = 0; i < int( s.size() ); ++i )
        if ( s[ i ] != s[ s.size() - i - 1 ] )
            return false;
    return true;
}
