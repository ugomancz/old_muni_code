/* We will first look at using std::string. Our first goal will be to implement
 * a simple word wrapping (paragraph filling) algorithm. */

#include <string>
#include <cassert>

/* «Input»: An ‹std::string› with ASCII text (letters, spaces,
 * newlines and punctuation) and ‹columns› (a number of columns).
 * Each line of the input text represents a single paragraph.
 *
 * «Output»: A string in which there are actual paragraphs with line
 * breaks, not too far after the given column number. That is, at
 * most a single word crosses the ‹column›-th column. Newlines in
 * the input are replaced by double newlines in the output. */

std::string fill( const std::string &in, int columns ) {
    std::string output;
    int currentColumns = 1;
    for ( char letter : in) {
        if (std::isspace(letter) and currentColumns >= columns) {
            if (letter == '\n') {
                output.push_back('\n');
                output.push_back('\n');
            } else {
                output.push_back('\n');
            }
            currentColumns = 1;
        } else {
            currentColumns++;
            output.push_back(letter);
        }
    }
    return output;
}

int main()
{
    /* Notice the string comparison using ‹==› in the assertions. */

    assert( fill( "hello world\n"
                  "bye world\n", 5 )
               == "hello\n"
                  "world\n\n"

                  "bye world\n\n" );

    assert( fill( "lorem ipsum dolor sit amet, "
                  "consectetaur adipisicing", 8 )
               == "lorem ipsum\n"
                  "dolor sit\n"
                  "amet, consectetaur\n"
                  "adipisicing" );

    assert( fill( "lorem ipsum dolor sit amet, "
                  "consectetaur adipisicing", 27 )
               == "lorem ipsum dolor sit amet,\n"
                  "consectetaur adipisicing" );

    assert( fill( "hello, world", 3 )
               == "hello,\n"
                  "world" );
}
