#include <iostream>

void f(int x) {
	std::cout << "int: " << x << '\n';
}

void f() {
	std::cout << "no parameters\n";
}

// try changing double to float; what happens?
void f(double d) {
	std::cout << "double: " << d << '\n';
}

int main() {
	f(42);    // try adding u suffix
	f(3.14);  // try adding f suffix
	f();
}
