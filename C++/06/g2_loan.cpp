/* Let us revisit the bank account story from first week. We will
 * have 2 classes this time: an ‹account›, which has the usual
 * methods: ‹deposit›, ‹withdraw›, ‹balance›; to simplify things, we
 * will only add a default constructor, which sets the initial
 * balance to 0.
 *
 * The other class will be called ‹loan›, and its constructor will
 * take a reference to an ‹account› and the amount loaned (an
 * ‹int›). Constructing a ‹loan› object will deposit the loaned
 * amount to the referenced account. It will also have a method
 * called ‹repay› which takes an integer, which withdraws the given
 * amount from the associated account and reduces the amount owed by
 * the same sum. Attempting to repay more than is owed should throw
 * ‹std::out_of_range›.
 *
 * Make sure that we can't accidentally destroy a ‹loan› without
 * repaying it first. Does it make sense to make a copy of a ‹loan›?
 * How about move? And assignment? */

#include <cassert>
#include <utility>
#include <stdexcept>

class account {
private:
    int _balance = 0;
public:
    void deposit(int sum) noexcept {
        _balance += sum;
    }

    void withdraw(int sum) noexcept {
        _balance -= sum;
    }

    int balance() const noexcept {
        return _balance;
    }
};

class loan {
private:
    account &acc;
    int loan_sum;
public:
    loan(account &acc, int loan) noexcept : acc(acc), loan_sum(loan) {
        assert(loan > 0);
        acc.deposit(loan);
    }

    loan(loan &&other) noexcept: acc(other.acc), loan_sum(std::exchange(other.loan_sum, 0)) {}

    loan(const loan &) = delete;

    void repay(int sum) {
        if (sum > loan_sum) {
            throw std::out_of_range("You can't pay more than you owe.");
        }
        acc.withdraw(sum);
        loan_sum -= sum;
    }

    ~loan() {
        acc.withdraw(loan_sum);
    }

    loan &operator=(loan &&other) noexcept {
        acc = other.acc;
        loan_sum = std::exchange(other.loan_sum, 0);
        return *this;
    }

    loan &operator=(const loan &) = delete;
};

int main()
{
    account a;

    {
        loan l( a, 1000 );
        assert( a.balance() == 1000 );
        l.repay( 100 );
        assert( a.balance() == 900 );
        a.deposit( 200 );
    }

    assert( a.balance() == 200 );

    {
        loan l( a, 500 );
        loan m = std::move( l );
        a.withdraw( 300 );
        assert( a.balance() == 400 );
        m.repay( 50 );

        bool caught = false;
        try { l.repay( 50 ); }
        catch ( std::out_of_range & ) { caught = true; }
        assert( caught );
    }

    assert( a.balance() == -100 );

    // clang-tidy: -clang-analyzer-cplusplus.Move
}
