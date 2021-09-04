/* This exercise is worth «10 points». */

/* Implement function ‹rpn› which takes a single ‹std::string› as an
 * argument. The string contains single-digit constants, operators
 * ‹+› (addition), ‹d› (distance, i.e. absolute value of
 * difference), ‹*› (multiplication) and ‹s› (sum of the entire
 * stack), separated by exactly single space. If the string does not
 * conform to this description, throw ‹parse_error›. If there are
 * insufficient operands on the stack, throw ‹stack_empty›. In all
 * other cases, return an integer which is the topmost value on the
 * stack after the computation has finished.
 *
 * Examples:
 *
 *     "3 2 1 s" → 6
 *     "3 2 1 +" → 3
 *     "3 x 1 +" → parse_error
 *     "31 1 +" → parse_error
 *     "1 +" → stack_empty
 *     "s" → 0
 *     "" → parse_error
 *     " 1" → parse_error
 *     "1  2" → parse_error
 *
 * Notes:
 *
 *  - RPN operates on a stack of numbers: constants push themselves
 *    onto the stack, operators pop their operands and push the
 *    result
 *  - the initial stack is empty
 *  - an empty input string is a parse error */

#include <cassert>
#include <exception>
#include <vector>
#include <string>
#include <set>
#include <numeric>

struct parse_error : std::exception {
};
struct stack_empty : std::exception {
};

const std::set<char> legit_nums = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const std::set<char> legit_ops = {'s', 'd', '+', '*'};

void sum(std::vector<int> &stack) {
    int result = std::accumulate(stack.begin(), stack.end(),0);
    stack.clear();
    stack.emplace_back(result);
}

void mul(std::vector<int> &stack) {
    if (stack.size() < 2) {
        throw stack_empty();
    }
    int first = stack.back();
    stack.pop_back();
    int second = stack.back();
    stack.pop_back();
    stack.emplace_back(first * second);
}

void dist(std::vector<int> &stack) {
    if (stack.size() < 2) {
        throw stack_empty();
    }
    int first = stack.back();
    stack.pop_back();
    int second = stack.back();
    stack.pop_back();
    stack.emplace_back(std::abs(first - second));
}

void add(std::vector<int> &stack) {
    if (stack.size() < 2) {
        throw stack_empty();
    }
    int first = stack.back();
    stack.pop_back();
    int second = stack.back();
    stack.pop_back();
    stack.emplace_back(first + second);
}

int rpn(const std::string &in) {
    if (in.empty() || in.size() % 2 == 0) {
        throw parse_error();
    }
    std::vector<int> stack;
    for (size_t i = 0; i < in.size(); i++) {
        if (i % 2 == 1) {
            if (in[i] != ' ') { // missing whitespace
                throw parse_error();
            }
            continue;
        }
        if (legit_nums.find(in[i]) == legit_nums.end() && legit_ops.find(in[i]) == legit_ops.end()) { //  undefined char
            throw parse_error();
        }
        if (legit_nums.find(in[i]) != legit_nums.end()) { // current char is a number
            stack.emplace_back(in[i] - '0');
        } else { // current char is an operation
            try {
                switch (in[i]) {
                    case 's':
                        sum(stack);
                        break;
                    case 'd':
                        dist(stack);
                        break;
                    case '+':
                        add(stack);
                        break;
                    case '*':
                        mul(stack);
                        break;
                }
            } catch (...) {
                throw;
            }
        }
    }
    return stack.back();
}

/* What follows are «basic» test cases for your convenience. You can
 * add additional test cases into main(): they will be «not»
 * executed during evaluation, so it is okay to submit with broken
 * main. However, make sure to «not» alter the prototype. Write all
 * your code «before» main. */

int main()
{
    assert( rpn( "3 2 1 s" ) == 6 );
    assert( rpn( "3 2 1 +" ) == 3 );
    assert( rpn( "s" ) == 0 );

    auto no_parse = []( std::string s )
    {
        try { rpn( s ); assert( false ); }
        catch ( parse_error & ) {}
    };

    no_parse( "3 x 1 +" );
    no_parse( "31 1 +" );
    no_parse( "" );
    no_parse( " 1" );
    no_parse( "1  2" );

    try { rpn( "1 +" ); assert( false ); }
    catch ( stack_empty & ) {}

    return 0;
}
