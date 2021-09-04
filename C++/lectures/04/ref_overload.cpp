#include <iostream>

// try changing the type (e.g. to std::string)

void f(int&) {
	std::cout << "reference\n";
}

void f(const int&) {
	std::cout << "const reference\n";
}

// try uncommenting this one
/* void f(int &&) {
	std::cout << "rvalue reference\n";
} */

// uncommenting this one leads to ambiguity error
/* void f(int) {
	std::cout << "value\n";
} */

int main() {
	int x = 5;
	const int y = 7;

	f(x);
	f(y);
	f(9);

	int& ref = x;
	const int& cref = x;

	f(ref);
	f(cref);
}
