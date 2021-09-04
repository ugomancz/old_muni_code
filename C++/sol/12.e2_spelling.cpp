#include <fstream>
#include <set>
#include <string>

class spell
{
    std::set< std::string > _words;
public:

    spell( const char *fn )
    {
        std::ifstream words( fn );
        std::string word;
        while ( std::getline( words, word ) )
            _words.insert( word );
    }

    bool check( const std::string s ) const
    {
        return _words.count( s );
    }
};

#include "e2_spelling.cpp"
