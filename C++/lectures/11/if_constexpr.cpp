#include <iostream>
#include <type_traits>

template <typename T>
bool equal(const T& a, const T& b) {
	if constexpr(std::is_floating_point_v<T>) {
		return std::abs(a - b) < 0.0001;
	} else {
		return a == b;
	}
}

int main() {
	std::cout << equal(3, 4) << '\n';
	std::cout << equal(3.0, 3.00009) << '\n';
}
