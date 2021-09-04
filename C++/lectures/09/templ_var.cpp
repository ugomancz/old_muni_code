#include <iostream>

template<class T>
constexpr T pi = T(3.1415926535897932385L);

int main() {
	std::cout.precision(17);
	std::cout << pi<double> << '\n';
	std::cout << pi<float> << '\n';
	std::cout << pi<int> << '\n';
}
