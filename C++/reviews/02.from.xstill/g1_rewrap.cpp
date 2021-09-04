/* A different take on word-wrapping. The idea is very similar to last week –
 * break lines at the first opportunity after you ran out of space in your
 * current line. The twist: do this by modifying the input string.
 * Additionally, undo existing line breaks if they are in the wrong spot. */

#include <string>
#include <cassert>

void rewrap(std::string &str, int cols) {
    int count = 0;
    for (char &letter : str) {
        /** • chybí std::, je vhodné ho používat i když to může funguovat i bez
         ** něj, protože ta funkce je z C. **/
        /** • Alternativním jménům operátorů (and, or, not, …) se v C++
         ** vyhýbáme, jedná se o přežitek z doby, kdy na klávesnici chyběla část
         ** znaků, jinak do C++ nepatří. **/
        if (count >= cols and isspace(letter)) { // insert a newline
            letter = '\n';
            count = 0;
        } else if (count < cols and letter == '\n') { // line break in wrong spot
            letter = ' ';
        }
        count++;
    }
}

int main()
{
    std::string s = "lorem ipsum dolor sit amet";
    rewrap( s, 5 );
    assert( s == "lorem\nipsum\ndolor\nsit amet" );
    rewrap( s, 7 );
    assert( s == "lorem ipsum\ndolor sit\namet" );
    rewrap( s, 20 );
    assert( s == "lorem ipsum dolor sit\namet" );
    rewrap( s, 30 );
    assert( s == "lorem ipsum dolor sit amet" );
    rewrap( s, 1 );
    assert( s == "lorem\nipsum\ndolor\nsit\namet" );
}
