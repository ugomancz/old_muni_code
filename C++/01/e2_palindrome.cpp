#include <iostream>
#include <string>
#include <cassert>

/* Write a predicate which decides whether a given string is a
 * palindrome, i.e. reads the same in both directions. */

bool is_palindrome( const std::string &s ) {
    int i = 0;
    int j = s.length() - 1;
    while (i<=j) {
        if (s[i] != s[j]) {
            //std::cout << "false\n";
            return false;
            
        }
        i++;
        j--;
    }
    //std::cout << "true\n";
    return true;
}

int main()
{
    assert( is_palindrome( "eye" ) );
    assert( is_palindrome( "anna" ) );
    assert( is_palindrome( "rats live on no evil star" ) );
    assert( is_palindrome( "step on no pets" ) );
    assert( !is_palindrome( "pie" ) );
}
