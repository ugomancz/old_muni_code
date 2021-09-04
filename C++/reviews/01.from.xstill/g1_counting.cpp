/* In this exercise, we will work with strings in a read-only way:
 * by counting things in them. Write two functions, ‹word_count› and
 * ‹line_count›: the former will count words (runs of characters
 * without spaces) and the latter will count the number of non-empty
 * lines. Use range ‹for› to look at the content of the string. */

#include <string>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <iterator>

/* Here are the prototypes of the functions -- you can simply turn
 * those into definitions. We pass arguments by ‹const› references:
 * for now, consider this to be a bit of syntax, the purpose of
 * which is to avoid making a copy of the string. It will be
 * explained in more detail later. Also notice that in a prototype,
 * the arguments do not need to be named (but you will have to give
 * them names to use them). */

int word_count(const std::string &input) {
    /** já bych se přikláněl k tomu tam to std:: psát explicitně ať je jasné, co
     ** je standardní funkce **/
    using namespace std;
    istringstream iss(input);
    /** zajímavé řešení… nicméně ten vector je trochu zbytečný, stačilo by
     ** vrátit std::distance těch dvou iterátorů (když už to řešíte technikami,
     ** které zatím nebyly probrané) **/
    vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};
    return tokens.size();
}

int line_count(const std::string &input) {
    int nonempty_lines = 0;
    std::istringstream stream(input);
    std::string buffer;
    while (std::getline(stream, buffer)) {
        /** pro přehlednost bych tělo té podmínky dal na samostatný řádek **/
        if (!std::all_of(buffer.begin(), buffer.end(), isspace)) nonempty_lines++;
    }
    return nonempty_lines;
}

int main()
{
    assert( line_count( "hello\nworld" ) == 2 );
    assert( line_count( "hello\nworld\n" ) == 2 );
    assert( line_count( "hello\n\nworld\n" ) == 2 );
    assert( line_count( "\nhello\n\nworld\n" ) == 2 );
    assert( line_count( "\nhello\n \nworld\n" ) == 2 );
    assert( line_count( "x" ) == 1 );
    assert( line_count( "x\n" ) == 1 );
    assert( line_count( "" ) == 0 );

    assert( word_count( "hello" ) == 1 );
    assert( word_count( "hello world" ) == 2 );
    assert( word_count( "hello world " ) == 2 );
    assert( word_count( "hello\nworld " ) == 2 );
    assert( word_count( "" ) == 0 );
}
