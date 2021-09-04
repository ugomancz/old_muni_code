#include "e3_split.cpp"

split_view split( std::string_view s, char delim )
{
    size_t idx = s.find( delim );
    if ( idx == s.npos )
        return { s, "" };
    else
        return { s.substr( 0, idx ), s.substr( idx + 1, s.npos ) };
}
