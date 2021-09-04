#include "f1_wrap.cpp"

std::string fill( const std::string &in, int columns )
{
    std::string out;
    int col = 0;

    for ( char c : in )
        if ( std::isblank( c ) && col >= columns )
            out += '\n', col = 0;
        else if ( c == '\n' )
            out += "\n\n", col = 0;
        else
            out += c, ++ col;

    return out;
}
