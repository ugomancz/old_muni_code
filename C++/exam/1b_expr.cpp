#include <string_view>
#include <map>
#include <cassert>
#include <stdexcept>
#include <utility>
#include <vector>
#include <variant>

/* Parsing and evaluating simple expressions, 10 points. */

/* A type which represents parsed expressions. The representation
 * and interface is entirely up to you. An expression is a sum
 * (additions and subtractions) of clauses where each clause is a
 * product (multiplication) of at most a single constant and some
 * (zero or more) variables. */

using values_t = std::map<char, int>;

struct clause {
    const int constant = 1;
    std::string variables;

    clause(const int c, std::string v) : constant(c), variables(std::move(v)) {};

    int eval(const values_t &v) {
        int result = constant;
        for (auto c : variables) {
            if (v.find(c) == v.end()) {
                throw std::out_of_range("dafsdfasdf");
            }
            result *= v.at(c);
        }
        return result;
    }
};

enum class op {
    ADD, SUB, NONE
};


int add(op operand, int left, clause right, const values_t &v) {
    switch (operand) {
        case op::ADD:
            return left + right.eval(v);
        case op::SUB:
            return left - right.eval(v);
        case op::NONE:
            break;
    }
    return 0;
}

struct expr {
    std::vector<std::pair<clause, op>> ex;

    explicit expr(std::vector<std::pair<clause, op>> e) : ex(std::move(e)) {};

    int eval(const values_t &v) const {
        int result = 0;
        op prev_op = op::ADD;
        for (auto &[c, o] : ex) {
            if (o == op::NONE) {
                return add(prev_op, result, c, v);
            }
            result = add(prev_op, result, c, v);
            prev_op = o;
        }
        return result;
    }
};

struct parse_error : std::exception {
};

/* Write a simple expression parser; the input expressions have the
 * following format:
 *
 *     expr     = clause | clause, op, expr ;
 *     clause   = ( constant | variable ), { variable } ;
 *     op       = space, ( '+' | '-' ), space ;
 *     variable = ? a single letter (std::isalpha) ? ;
 *     constant = ? a single digit (std::isdigit) ? ;
 *     space    = ? zero or more spaces (std::isspace) ? ;
 *
 * If the input string does not «exactly» conform to the grammar,
 * ‹parse› «must» throw a ‹parse_error›. */

enum class sign {
    PLUS, MINUS, NONE
};

void parse_lexeme(std::string lexeme, std::vector<std::pair<clause, op>> &parsed_expr, sign flag) {
    try {
        int constant = 1;
        if (std::isdigit(lexeme[0])) {
            constant = lexeme[0] - '0';
            lexeme.erase(lexeme.begin());
        }
        for (char c : lexeme) {
            if (!std::isalpha(c)) {
                throw parse_error();
            }
        }
        if (flag == sign::PLUS) {
            parsed_expr.emplace_back(std::pair<clause, op>(clause(constant, lexeme), op::ADD));
            return;
        }
        if (flag == sign::MINUS) {
            parsed_expr.emplace_back(std::pair<clause, op>(clause(constant, lexeme), op::SUB));
            return;
        }
        if (flag == sign::NONE) {
            parsed_expr.emplace_back(std::pair<clause, op>(clause(constant, lexeme), op::NONE));
            return;
        }
        throw parse_error();

    } catch (...) {
        throw;
    }

}

expr parse(std::string_view input) {
    if (input.empty() || std::isspace(input[0]) || std::isspace(input.back()) || input[0] == '+' || input[0] == '-' || input.back() == '+' || input.back() == '-') {
        throw parse_error();
    }
    std::vector<std::pair<clause, op>> parsed_expr;
    try {
        std::string lexeme;
        bool was_space = false;
        for (char c : input) {
            if (was_space && !std::isspace(c) && !(c == '+' || c == '-')) {
                throw parse_error();
            }
            if ((c == '+' || c == '-')) {
                if (lexeme.empty()) {
                    throw parse_error();
                }
                parse_lexeme(lexeme, parsed_expr, (c == '+') ? sign::PLUS : sign::MINUS);
                lexeme = "";
                was_space = false;
                continue;
            }
            if (!std::isspace(c)) {
                lexeme += c;
            } else if (!lexeme.empty()) {
                was_space = true;
            }
        }
        if (!lexeme.empty()) {
            parse_lexeme(lexeme, parsed_expr, sign::NONE);
            lexeme = "";
        }
    } catch (...) {
        throw;
    }
    return expr(parsed_expr);
}

/* Evaluate a parsed expression. The second argument gives a value
 * to each variable. Throw ‹std::out_of_range› if the expression
 * contains a variable not present in the map. */


int eval(const expr &ex, const values_t &v) {
    return ex.eval(v);
}

/* What follows are «basic» test cases for your convenience. You can
 * add additional test cases into main(): they «will not» be
 * executed during evaluation, so it is okay to submit with broken
 * main. However, make sure to «not» alter the line with the
 * prototype. */

int main() {
    auto check_throws = [](std::string_view s) {
        try {
            parse(s);
            assert(false);
        }
        catch (const parse_error &) {}
    };

    auto pe = [](std::string_view s, values_t v) {
        expr e = parse(s);
        return eval(e, v);
    };

    check_throws("11");
    check_throws(" 1");
    check_throws("x1");
    check_throws("1 + 11");
    check_throws("1 * 1");
    check_throws("         1 * 1");
    check_throws("         1 * 1      ");
    check_throws("         ");
    check_throws("");
    check_throws("+");
    check_throws("*");
    check_throws("99");
    check_throws("x ");
    check_throws("x y");
    check_throws("x+y+");
    check_throws("x++");
    check_throws("x++y");
    check_throws("x9+y");
    check_throws("+y");
    check_throws("1 1");
    check_throws("1+1*");


    assert(pe("1", {}) == 1);
    assert(pe("1 + 2xy", {{'x', 0},
                          {'y', 0}}) == 1);
    assert(pe("1 + 2yx", {{'x', 0},
                          {'y', 0}}) == 1);
    assert(pe("1xy - 1yx", {{'x', 1},
                            {'y', 1}}) == 0);
    assert(pe("1xxxxxxxxxxxxxxxxxxxxxx       -        1yx", {{'x', 1},
                                                             {'y', 1}}) == 0);
    assert(pe("1xxxxxxxxxxxxxxxxxxxxxx       + 1yxyxyxyxyxy", {{'x', 1},
                                                               {'y', 1}}) == 2);
    assert(pe("1xxxxxxxxxxxxxxxxxxxxxx +      5yxyxyxyxyxy", {{'x', 1},
                                                              {'y', 1}}) == 6);
    assert(pe("1x  + 5y", {{'x', 9},
                           {'y', 9}}) == 54);
    assert(pe("1x+5y", {{'x', 10},
                        {'y', 9}}) == 55);
    assert(pe("1xz  + 5y", {{'x', 10},
                            {'y', 2},
                            {'z', 3}}) == 40);
    assert(pe("1+1", {}) == 2);
    assert(pe("1 - 1", {}) == 0);
    assert(pe("x", {{'x', 1}}) == 1);
    assert(pe("xx + 2xy + yy", {{'x', 1},
                                {'y', 0}}) == 1);

    try {
        pe("xy", {{'x', 1}});
        assert(false);
    }
    catch (const std::out_of_range &) {}

    return 0;
}
