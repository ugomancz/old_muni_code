#include <iostream>

struct Base {
	int value;
	explicit Base(int v) : value(v) {
		std::cout << "Base ctor with " << v << '\n';
	}
};

struct Derived : Base {
	using Base::Base;
	Derived() : Base(1) { std::cout << "Derived ctor\n"; }
};

int main() {
	Derived d1;
	std::cout << d1.value << '\n';
	Derived d2(2);
	std::cout << d2.value << '\n';
}
