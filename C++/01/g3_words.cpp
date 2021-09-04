/* Write a function that breaks up a string into individual words. We consider
 * a word to be any string without whitespace (spaces, newlines, tabs) in it. */

#include <vector>
#include <string>
#include <cassert>
#include <iterator>
#include <sstream>

/* Since we are lazy to type the long-winded type for a vector of
 * strings, we define a «type alias». The syntax is different from C,
 * but it should be clearly understandable. We will encounter this
 * construct many times in the future. */

using string_vec = std::vector< std::string >;

/* The output of ‹words› should be a vector of strings, where each
 * of the strings contains a single word from ‹in›. */

string_vec words( const std::string &in ) {
    using namespace std;
    istringstream iss(in);
    return vector<string>{istream_iterator<string>{iss},
                          istream_iterator<string>{}};
}

int main()
{
    assert( ( words( "lorem ipsum dolor" ) ==
              string_vec{ "lorem", "ipsum", "dolor" } ) );
    assert( ( words( "hello, world" ) == string_vec{ "hello,", "world" } ) );
    assert( ( words( "hello  world" ) == string_vec{ "hello", "world" } ) );
    assert( ( words( "hello\nworld\n" ) == string_vec{ "hello", "world" } ) );
    assert( ( words( " hello \n world" ) == string_vec{ "hello", "world" } ) );
}
