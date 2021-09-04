#include <string>
#include <stdexcept>

int stoi_or( std::string s, int def )
{
    try
    {
        return std::stoi( s );
    }
    catch ( std::out_of_range & )
    {
        return def;
    }
    catch ( std::invalid_argument & )
    {
        return def;
    }
}

#include "e1_default.cpp"
