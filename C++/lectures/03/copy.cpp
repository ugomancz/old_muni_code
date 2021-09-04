#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

int main() {
	std::set s = { 0, 21, -7, 4 };

	std::vector<int> vec;
	vec.resize(7);
	// vec is { 0, 0, 0, 0, 0, 0, 0 }

	std::copy(s.begin(), s.end(), vec.begin() + 2);
	// vec is { 0, 0, -7, 0, 4, 21, 0 }

	for (int x : vec) {
		std::cout << x << ' ';
	}
	std::cout << '\n';

	std::copy(s.begin(), s.end(),
	          std::back_inserter(vec));

	s.clear();

	std::copy(vec.begin(), vec.end(),
	          std::inserter(s, s.end()));

	vec = { 1, 2, 3 };

	vec.insert(vec.end(), s.begin(), s.end());

	for (int x : s) {
		std::cout << x << ' ';
	}
	std::cout << '\n';

	std::array arr = { 1, 2, 3, 4, 5 };
	std::copy_if(s.begin(), s.end(), arr.begin(),
	             [](int num) { return num % 2 == 0; });
	// arr is { 0, 4, 3, 4, 5 };

	for (int x : arr) {
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
