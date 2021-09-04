/* To practice working with IO streams a little, we will write a two
 * simple functions which reads lines from an input stream, process
 * them a little and possibly print them out or their part into an
 * output stream. */

#include <cassert>
#include <sstream>
#include <string>
#include <vector>

/* The ‹grep› function checks, for every line on the input, whether
 * it matches a given ‹pattern› (i.e. the pattern is a substring of
 * the line) and if it does (and only if it does) copies the line to
 * the output stream. */

void grep(const std::string &pattern, std::istream &in, std::ostream &out) {
    std::string line;
    while (std::getline(in, line)) {
        if (line.find(pattern) != std::string::npos) {
            out << line << '\n';
        }
    }
}

/* The other function to add is called ‹cut› and it will process the
 * lines differently: it splits each line into fields separated by
 * the character ‹delim› and only prints the column given by ‹col›.
 * Unlike the ‹cut› program, index columns starting at 0. If there
 * are not enough columns on a given line, print an empty line. */

void cut(const char delim, const int col, std::istream &in, std::ostream &out) {
    std::string line;
    std::string token;
    std::vector<std::string> split;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        while (std::getline(iss, token, delim)) {
            split.emplace_back(token);
        }
        if (split.size() <= static_cast<size_t>(col)) {
            out << '\n';
        } else {
            out << split.at(col) << '\n';
        }
        split.clear();
    }
}

int main()
{
    const char *grep_in = "hello\nworld\nbye\nworld\n";
    const char *cut_in  = "a,b|c,d\ne|f|g,h\ni,j,k|l\n";

    auto check_grep = [&]( std::string pat, std::string expect )
    {
        std::istringstream istr( grep_in );
        std::ostringstream ostr;
        grep( pat, istr, ostr );
        assert( ostr.str() == expect );
    };

    check_grep( "o", "hello\nworld\nworld\n" );
    check_grep( "hell", "hello\n" );
    check_grep( "world", "world\nworld\n" );

    auto check_cut = [&]( char d, int c, std::string expect )
    {
        std::istringstream istr( cut_in );
        std::ostringstream ostr;
        cut( d, c, istr, ostr );
        assert( ostr.str() == expect );
    };

    check_cut( ',', 0, "a\ne|f|g\ni\n" );
    check_cut( ',', 1, "b|c\nh\nj\n" );
    check_cut( ',', 2, "d\n\nk|l\n" );
    check_cut( '|', 0, "a,b\ne\ni,j,k\n" );
    check_cut( '|', 1, "c,d\nf\nl\n" );
    check_cut( '|', 2, "\ng,h\n\n" );
}
