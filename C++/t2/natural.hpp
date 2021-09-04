#ifndef NATURAL_H
#define NATURAL_H

#include <vector>
#include <cstdint>

/* In this task, you will implement a class which represents
 * arbitrary-size natural numbers (including 0). In addition to the
 * methods prescribed below, the class must support the following
 * basic arithmetic operators: addition, subtraction,
 * multiplication, division, modulo, and all relational operators.
 * If the result of subtraction cannot be represented (i.e. would be
 * negative) throw ‹std::out_of_range›. */

class natural {
    std::vector<unsigned long long> digits;

    bool is_even() const;

    bool is_zero() const;

    void strip_zeros();

    uint8_t pop_first_num();

    void append_digits_reversed(natural mod);

    std::pair<natural, natural> digit_count_sum(const natural &base) const;

    friend std::pair<natural, natural> small_div_mod(natural dividend, const natural &divisor);

    friend std::pair<natural, natural> div_mod(natural &dividend, const natural &divisor);

    friend natural exp_by_square(const natural &left, const natural &right);

public:
    /* Construct a natural number, optionally from an integer. Throw
     * ‹std::out_of_range› if ‹v› is negative. */
    explicit natural(int v = 0);

    natural power( const natural& exponent ) const;

    natural digit_count(const natural &base) const;

    natural digit_sum(const natural &base) const;

    bool operator==(const natural &other) const;

    bool operator!=(const natural &other) const;

    bool operator<(const natural &other) const;

    bool operator>(const natural &other) const;

    bool operator<=(const natural &other) const;

    bool operator>=(const natural &other) const;

    natural &operator+=(const natural &other);

    natural &operator-=(const natural &other);

    natural operator*=(const natural &other);

    natural &operator/=(const natural &divisor);

    natural &operator%=(const natural &divisor);
};

natural operator+(natural left, const natural &right);

natural operator-(natural left, const natural &right);

natural operator*(natural left, const natural &right);

natural operator/(natural left, const natural &right);

natural operator%(natural left, const natural &right);

std::pair<natural, natural> small_div_mod(natural dividend, const natural &divisor);

std::pair<natural, natural> div_mod(natural &dividend, const natural &divisor);

natural exp_by_square(const natural &left, const natural &right);

/* Additionally, implement the following operations on natural
 * numbers as top-level functions: */

natural gcd(const natural &a, const natural &b);

natural lcm(const natural &a, const natural &b);

#endif
