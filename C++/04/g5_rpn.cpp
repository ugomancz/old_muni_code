/* Write a simple stack-based evaluator for numeric expressions in
 * an RPN form.  The operations:
 *
 *  • ‹push› takes a number and pushes it onto the working stack,
 *  • ‹apply› accepts an instance of one of the three operator
 *    classes defined below; like with the string builder earlier,
 *    both those methods should return a reference to the evaluator,
 *  • again like with the zipper, a ‹top› method should give access
 *    to the current top of the stack, including the possibility of
 *    changing the value,
 *  • ‹pop› which also returns the popped value, and
 *  • ‹empty› which returns a ‹bool›.
 *
 * All three operators are binary (take 2 arguments). */

#include <cassert>
#include <cmath>
#include <vector>

struct add {};  /* addition */
struct mul {};  /* multiplication */
struct dist {}; /* absolute value of difference */

class eval {
private:
    std::vector<int> stack;

    std::pair<int, int> pop_tops() {
        assert(stack.size() >= 2);
        std::pair<int, int> pair{stack.at(stack.size() - 1), stack.at(stack.size() - 2)};
        stack.resize(stack.size() - 2);
        return pair;
    }

public:
    eval &push(int value) {
        stack.emplace_back(value);
        return *this;
    }

    int pop() {
        int popped = stack.at(stack.size() - 1);
        stack.pop_back();
        return popped;
    }

    int top() const {
        return stack.at(stack.size() - 1);
    }

    int &top() {
        return stack.at(stack.size() - 1);
    }

    bool empty() const {
        return stack.empty();
    }

    eval &apply(add) {
        auto pair = pop_tops();
        push(pair.first + pair.second);
        return *this;
    }

    eval &apply(mul) {
        auto pair = pop_tops();
        push(pair.first * pair.second);
        return *this;
    }

    eval &apply(dist) {
        auto pair = pop_tops();
        push(std::abs(pair.first - pair.second));
        return *this;
    }
};

int main()
{
    eval e;
    const eval &f = e;

    e.push( 7 ).push( 3 ).apply( add() );
    assert( f.top() == 10 );
    assert( e.push( 1 ).apply( mul() ).top() == 10 );
    assert( e.pop() == 10 );
    assert( f.empty() );
    e.push( 10 );
    e.top() = 11;
    assert( f.top() == 11 );
    e.push( 10 ).apply( dist() );
    assert( f.top() == 1 );
    assert( !f.empty() );
    assert( e.pop() == 1 );
    assert( f.empty() );
}
