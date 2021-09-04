#include <iostream>

template <typename T>
const T& max(const T& x, const T& y) {
	return x < y ? y : x;
}

class NotComparable {};

int main() {
	int a, b;
	std::cin >> a >> b;

	std::cout << max<int>(a, b) << '\n';

	// NotComparable nc1, nc2;
	// auto x = max(nc1, nc2);

	// template deduction
	std::cout << max<>(a, b) << '\n';
	std::cout << max(a, b) << '\n';

	unsigned long c = 17;

	// std::cout << max(a, c) << '\n'; // error

	std::cout << max<unsigned long>(a, c) << '\n';

}
