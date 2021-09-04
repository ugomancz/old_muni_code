#include <cassert>
#include <iostream>

class MaybeInt {
	bool _just = false;
	int _value{};

public:
	MaybeInt() {
		std::cout << "() constructor\n";
	}

	MaybeInt(int v) : _just(true), _value(v) {
		std::cout << "(int) constructor\n";
	}

	MaybeInt& operator=(int v) {
		std::cout << "assignment operator\n";
		_just = true;
		_value = v;
		return *this;
	}

	bool has_value() const {
		return _just;
	}

	int value() const {
		assert(has_value());
		return _value;
	}
};

int main() {
	// initialisation calls the constructor
	MaybeInt m1 = 1;

	MaybeInt m2;

	// assignment calls the assignment operator
	m2 = 2;

	std::cout << m1.value() << ' ' << m2.value() << '\n';
}
