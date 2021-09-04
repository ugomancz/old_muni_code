/* It is probably easiest to implement this using ‹std::getline› to
 * fetch both lines and individual cells. Other approaches are
 * certainly possible though. */

#include <sstream>
#include <iostream>
#include <vector>

class bad_format {};

class csv
{
    std::vector< std::vector< int > > data;
public:

    /* Process a single line, with some rudimentary format
     * validation. The ‹std::stoi› call will throw if the number
     * cannot be parsed, but will not complain about trailing
     * garbage. */

    void process_line( const std::string &line, int cols )
    {
        std::istringstream i_line( line );
        std::string cell;

        data.emplace_back();

        for ( int i = 0; i < cols; ++i )
        {
            if ( !std::getline( i_line, cell, ',' ) )
                throw bad_format();
            data.back().push_back( std::stoi( cell ) );
        }

        i_line.get();

        if ( !i_line.eof() )
            throw bad_format();
    }

    /* The constructor, fetches lines until it reaches the end of
     * the file and processes each of them using the above. */

    csv( std::istream &i, int cols )
    {
        std::string line;

        while ( std::getline( i, line ) )
            process_line( line, cols );
    }

    /* The indexing operator. Since we want ‹[ x ][ y ]› to work, we
     * need to return something with an indexing operator of its own
     * here. The easiest thing to do is to return the underlying
     * ‹vector› in which we store the row. It would be possible to
     * return a proxy object too. */

    std::vector< int > &operator[]( int i )
    {
        return data[ i ];
    }
};

#include "f2_csv.cpp"
