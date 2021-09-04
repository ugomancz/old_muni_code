/** pokud chcete dostat feedback na konkrétní příklad, nebo na konkrétní místo v
 ** něm, můžete ho označit v souboru, ideálně napsat do hlavičky prvního
 ** odevzdaného příkladu ve kterém něco takového máte. Budu ho pak
 ** prioritizovat. **/

#include <deque>
#include <string>
#include <cassert>

/* Check that curly and square brackets in a given string balance
 * out correctly. */

bool balanced(const std::string &in) {
    /** na stack je lepší použít vektor, deque je třeba na frontu – vektor je ve
     ** většině případů kdy se přidává a odebírá jen na konci efektivnější **/
    std::deque<char> stack;
    for (auto &letter : in) {
        switch (letter) {
            case '{':
            case '[':
                stack.push_back(letter);
                break;
            case '}':
            case ']':
                /** jako zajímavý trik… ale čtenář fakt netuší, co to ‹- 2›
                 ** dělá, takže to opravdu není hezký kód. Navíc standard
                 ** nedefinuje, že hodnoty jednotlivých základních znaků budou
                 ** odpovídat ASCII **/
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
