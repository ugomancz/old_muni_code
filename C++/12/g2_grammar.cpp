/* A regular grammar has rules of the form ⟦A → xB⟧ or ⟦A → x⟧ where
 * ⟦A⟧ and ⟦B⟧ are non-terminals and ⟦x⟧ is a terminal. */

#include <cassert>
#include <string>
#include <vector>
#include <map>

/* Implement a class ‹grammar›, which is default-constructable and
 * has 2 methods:
 *
 *  • ‹add_rule›, which takes 2 or 3 arguments: a single ‹char› for
 *    the left-hand non-terminal (a capital alphabetic letter), a
 *    terminal and optionally another non-terminal,
 *  • ‹generate›, a ‹const› method which takes 2 arguments: the
 *    starting non-terminal and an integer which gives the maximum
 *    length of a word, and returns an ‹std::vector› of ‹std::string›
 *    with all the «words» the grammar can generate (within the given
 *    size bound), sorted lexicographically. */

class grammar {
private:
    std::map<char, std::vector<std::string>> rules;

    void generate_rec(std::string word, const size_t max_length, std::vector<std::string> &language) const {
        if (word.length() <= max_length && std::islower(word.back())) { // whole word generated
            language.emplace_back(word);
            return;
        }
        if (rules.find(word.back()) == rules.end() ||
            word.length() > max_length) { // no available rules or word too long
            return;
        }
        for (const std::string &right : rules.at(word.back())) {
            auto new_word = word;
            new_word.pop_back();
            generate_rec(new_word += right, max_length, language);
        }
    }

public:
    void add_rule(const char left, const char terminal) {
        rules[left].emplace_back(std::string{terminal});
    }

    void add_rule(const char left, const char terminal, const char non_terminal) {
        rules[left].emplace_back(std::string{terminal} += non_terminal);
    }

    std::vector<std::string> generate(const char init, int max_length) const {
        std::vector<std::string> language;
        std::string first_word{init};
        generate_rec(first_word, static_cast<size_t>(max_length), language);
        return language;
    }
};

int main()
{
    auto w = []( auto... words ) /* helper function */
    {
        return std::vector< std::string >{ words... };
    };

    grammar g;
    const grammar &cg = g;

    assert( cg.generate( 'A', 10 ) == w() );
    g.add_rule( 'A', 'a' );
    assert( cg.generate( 'A', 10 ) == w( "a" ) );

    g.add_rule( 'A', 'b', 'A' );
    assert( cg.generate( 'A', 3 ) == w( "a", "ba", "bba" ) );

    g.add_rule( 'A', 'x', 'X' );
    g.add_rule( 'X', 'x' );
    assert( cg.generate( 'A', 3 ) == w( "a", "ba", "bba", "bxx", "xx" ) );
    g.add_rule( 'X', 'x', 'X' );
    assert( cg.generate( 'X', 3 ) == w( "x", "xx", "xxx" ) );
}
