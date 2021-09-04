#include <iostream>

template <typename T, typename U>
T convert(const U& value) {
	return static_cast<T>(value);
};

int main() {
	// std::cout << convert(3.14) << '\n'; // ERROR
	std::cout << convert<int, double>(3.14) << '\n';
	std::cout << convert<int>(3.14) << '\n';
}
