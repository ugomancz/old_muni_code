#include <cmath>
#include <iostream>
#include <numeric>

class Fraction {
	int _num = 0;
	int _denom = 1;

public:
	Fraction() = default;

	// this will be used in implicit casts int -> Fraction
	Fraction(int num, int denom = 1) : _num(num), _denom(denom) {
		_normalize();
	}

	// implicit cast; try adding explicit
	operator double() const {
		return static_cast<double>(_num) / _denom;
	}

	// try commenting this out
	friend std::ostream& operator<<(std::ostream& out,
	                                Fraction& f) {
		return out << f._num << '/' << f._denom;
	}

	/*
	explicit operator bool() const {
		return _num != 0;
	}
	*/

private:
	void _normalize() {
		int d = std::gcd(_num, _denom);
		_num /= d;
		_denom /= d;
	}
};

int main() {
	Fraction one = 1;
	Fraction pi_approx(22, 7);

	std::cout << one << '\n';
	std::cout << pi_approx << '\n';

	std::cout << std::sqrt(pi_approx) << '\n';

	if (one) {
		std::cout << "one is true\n";
	}
}
