#include <iostream>

constexpr int factorial(int num) {
	return num <= 1 ? 1 : num * factorial(num - 1);
}

int main() {
	// not VLA! the size is known at compile time
	int array[factorial(7)];

	std::cout << sizeof(array) / sizeof(int) << '\n';
}
