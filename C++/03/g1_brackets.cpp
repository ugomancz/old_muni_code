#include <deque>
#include <string>
#include <cassert>

/* Check that curly and square brackets in a given string balance
 * out correctly. */

bool balanced(const std::string &in) {
    std::deque<char> stack;
    for (auto &letter : in) {
        switch (letter) {
            case '{':
            case '[':
                stack.push_back(letter);
                break;
            case '}':
            case ']':
                if (stack.empty() || stack.back() != letter - 2) {
                    return false;
                } else {
                    stack.pop_back();
                }
                break;
            default:
                break;
        }
    }
    return stack.empty();
}

int main()
{
    assert(  balanced( "{}" ) );
    assert(  balanced( "{(}" ) );
    assert(  balanced( "{{}}" ) );
    assert(  balanced( "{[]}" ) );
    assert(  balanced( "{[][]}" ) );
    assert(  balanced( "{[][]}[]" ) );
    assert( !balanced( "{[}]" ) );
    assert( !balanced( "{" ) );
    assert( !balanced( "]" ) );
    assert(  balanced( "{[x]y[z]} [x]" ) );
}
