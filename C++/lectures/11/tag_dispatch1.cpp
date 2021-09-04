#include <iostream>
#include <type_traits>

template <typename T>
bool equal_impl(const T& a, const T& b, std::false_type) {
	return a == b;
}

template <typename T>
bool equal_impl(const T& a, const T& b, std::true_type) {
	return std::abs(a - b) < 0.0001;
}

template <typename T>
bool equal(const T& a, const T& b) {
	return equal_impl(a, b,
	                  std::is_floating_point<T>{});
}

int main() {
	std::cout << equal(3, 4) << '\n';
	std::cout << equal(3.0, 3.00009) << '\n';
}
