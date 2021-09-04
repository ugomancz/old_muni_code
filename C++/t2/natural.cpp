#include <algorithm>
#include <stdexcept>
#include "natural.hpp"

natural::natural(int v) {
    if (v < 0) {
        throw std::out_of_range("Natural cannot be a negative number.");
    }
    while (v > 0) {
        digits.emplace_back(v % 10);
        v /= 10;
    }
}

natural natural::power(const natural& exponent) const {
    return exp_by_square(*this, exponent);
}

natural natural::digit_count(const natural &base) const {
    return digit_count_sum(base).first;
}

natural natural::digit_sum(const natural &base) const {
    return digit_count_sum(base).second;
}

bool natural::operator==(const natural &other) const {
    if (digits.size() != other.digits.size()) {
        return false;
    }
    for (size_t i = 0; i < digits.size(); i++) {
        if (digits[i] != other.digits[i]) {
            return false;
        }
    }
    return true;
}

bool natural::operator!=(const natural &other) const {
    return !(*this == other);
}

bool natural::operator<(const natural &other) const {
    try {
        auto copy = *this;
        copy -= other;
        return false;
    } catch (std::out_of_range &ex) {
        return true;
    }
}

bool natural::operator>(const natural &other) const {
    return other < *this;
}

bool natural::operator<=(const natural &other) const {
    return !(other < *this);
}

bool natural::operator>=(const natural &other) const {
    return !(*this < other);
}

natural &natural::operator+=(const natural &other) {
    auto copy = other;
    uint8_t carried = 0;
    if (copy == natural(0)) {
        return *this;
    }
    if (copy.digits.size() > digits.size()) {
        digits.resize(copy.digits.size() + 1);
        copy.digits.resize(digits.size());
    } else {
        digits.emplace_back(0);
        copy.digits.resize(digits.size());
    }
    size_t i;
    for (i = 0; i < copy.digits.size(); i++) {
        auto new_carried = digits[i] + copy.digits[i] + carried;
        carried = new_carried / 10;
        digits[i] = new_carried % 10;
    }
    strip_zeros();
    return *this;
}

natural &natural::operator-=(const natural &other) {
    if (other == natural(0)) {
        return *this;
    }
    if (other.digits.size() > digits.size()) {
        throw std::out_of_range("Result of -= operation cannot be a negative number.");
    }
    auto copy = other;
    copy.digits.resize(digits.size());
    long long borrow = 0, diff;
    for (size_t i = 0; i < copy.digits.size(); i++) {
        diff = digits[i] - copy.digits[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        digits[i] = diff;
    }
    if (borrow == 1) {
        throw std::out_of_range("Result of -= operation cannot be a negative number.");
    }
    strip_zeros();
    return *this;
}

natural natural::operator*=(const natural &other) {
    if (other == natural(0)) {
        digits.clear();
        return *this;
    }
    std::vector<unsigned long long> temp_digits;
    temp_digits.resize(digits.size() + other.digits.size());
    for (size_t i = 0; i < digits.size(); i++) {
        for (size_t j = 0; j < other.digits.size(); j++) {
            temp_digits[i + j] += other.digits[j] * digits[i];
        }
    }
    for (size_t i = 0; i < temp_digits.size(); i++) {
        if (temp_digits[i] >= 10) {
            temp_digits[i + 1] += temp_digits[i] / 10;
            temp_digits[i] %= 10;
        }
    }
    digits = temp_digits;
    strip_zeros();
    return *this;
}

natural &natural::operator/=(const natural &divisor) {
    const auto[div, mod] = div_mod(*this, divisor);
    *this = div;
    return *this;
}


natural &natural::operator%=(const natural &divisor) {
    const auto[div, mod] = div_mod(*this, divisor);
    *this = mod;
    return *this;
}

bool natural::is_even() const {
    if (digits.empty()) {
        return true;
    }
    return (digits[0] % 2 == 0);
}

bool natural::is_zero() const {
    return digits.empty();
}

void natural::strip_zeros() {
    if (digits.empty()) return;
    while (!digits.empty() && *(digits.end() - 1) == 0) {
        digits.pop_back();
    }
}

uint8_t natural::pop_first_num() {
    auto temp = *(digits.end() - 1);
    digits.pop_back();
    return temp;
}

void natural::append_digits_reversed(natural mod) {
    std::reverse(mod.digits.begin(), mod.digits.end());
    for (const auto digit : mod.digits) {
        digits.emplace_back(digit);
    }
}

std::pair<natural, natural> natural::digit_count_sum(const natural &base) const {
    auto copy = *this;
    natural digit_count;
    natural digit_sum;
    while (!copy.is_zero()) {
        const auto[div, mod] = div_mod(copy, base);
        digit_count += natural(1);
        digit_sum += mod;
        copy = div;
    }
    return {digit_count, digit_sum};
}

natural operator+(natural left, const natural &right) {
    left += right;
    return left;
}

natural operator-(natural left, const natural &right) {
    left -= right;
    return left;
}

natural operator*(natural left, const natural &right) {
    left *= right;
    return left;
}

natural operator/(natural left, const natural &right) {
    left /= right;
    return left;
}

natural operator%(natural left, const natural &right) {
    left %= right;
    return left;
}

std::pair<natural, natural> small_div_mod(natural dividend, const natural &divisor) {
    natural div_result;
    natural mod_result = dividend;
    while (true) {
        try {
            dividend -= divisor;
            mod_result -= divisor;
            div_result += natural(1);
        } catch (std::out_of_range &ex) {
            break;
        }
    }
    return {div_result, mod_result};
}

std::pair<natural, natural> div_mod(natural &dividend, const natural &divisor) {
    if (divisor == natural(0)) {
        throw std::out_of_range("Cannot divide by zero.");
    }
    if (divisor == natural(1)) {
        return {dividend, natural(0)};
    }
    natural result, smallest_available_dividend(0), mod(0);
    mod.digits.resize(divisor.digits.size() + 1);
    while (!dividend.is_zero()) {
        mod.digits.emplace(mod.digits.begin(), dividend.pop_first_num());
        mod.digits.pop_back();
        if (mod < divisor) {
            result.digits.emplace_back(0);
            continue;
        }
        auto[div, _mod] = small_div_mod(mod, divisor);
        result.append_digits_reversed(div);
        mod = _mod;
        mod.digits.resize(divisor.digits.size() + 1);
    }
    std::reverse(result.digits.begin(), result.digits.end());
    result.strip_zeros();
    mod.strip_zeros();
    return {result, mod};
}

natural exp_by_square(const natural &left, const natural &right) {
    if (right.is_zero()) {
        return natural(1);
    }
    if (right == natural(1)) {
        return left;
    }
    if (right.is_even()) {
        return exp_by_square(left * left, right / natural(2));
    }
    return left * exp_by_square(left * left, (right - natural(1)) / natural(2));
}

natural gcd(const natural &a, const natural &b) {
    if (b == natural(0)) {
        return a;
    }
    return gcd(b, a % b);
}

natural lcm(const natural &a, const natural &b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    /* tests go here */
}
