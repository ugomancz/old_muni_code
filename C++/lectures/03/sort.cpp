#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

int main() {
	int arr1[7] = { 17, 42, 1, 3, 3, 7, 0 };
	std::sort(arr1, arr1 + 7);

	// C++17 type deduction
	std::array arr2{ 17, 42, 1, 3, 3, 7, 0 };
	std::sort(arr2.begin(), arr2.end());

	std::vector vec1{ 17, 42, 1, 3, 3, 7, 0 };
	std::sort(vec1.begin(), vec1.end());

	std::vector vec2{ 17, 42, 1, 3, 3, 7, 0 };
	std::sort(vec2.begin() + 1, vec2.end() - 2);

	// we use a lambda with auto parameters to avoid
	// using templates here
	auto print = [](const auto& container) {
		for (auto& x : container) {
			std::cout << x << ' ';
		}
		std::cout << '\n';
	};

	print(arr1);
	print(arr2);
	print(vec1);
	print(vec2);

	auto it = std::find(vec2.begin(), vec2.end(), 42);
	std::sort(it, vec2.end());
	print(vec2);

	std::sort(vec2.begin(), it,
	          [](int x, int y) { return y < x; });
	print(vec2);

	std::sort(vec2.begin(), vec2.end(),
	          std::greater());
	print(vec2);
}
