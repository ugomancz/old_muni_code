#include <iostream>

template <unsigned N>
struct Factorial {
	static inline const size_t value =
		N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
	static inline const size_t value = 1;
};

template <unsigned N>
const size_t fact_value = Factorial<N>::value;

int main() {
	std::cout << Factorial<7>::value << '\n';

	// this is not a VLA! the value is known at compile time
	int array[fact_value<7>];

	std::cout << sizeof(array) / sizeof(int) << '\n';
}
