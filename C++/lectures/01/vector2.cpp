// Various kinds of vector initialization

#include <iostream>
#include <vector>

int main() {
	std::vector<int> v1 = { 1, 2, 7, 17, 42 };
	std::vector<int> v2{ 1, 2, 7, 17, 42 };
	std::vector<int> v3(10);
	std::vector<int> v4(10, 17);

	for (int x : v1) { // try v2, v3, v4
		std::cout << x << ' ';
	}
	std::cout << '\n';

	v1.resize(7); // changing the size of the vector

	for (int x : v1) {
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
