#include <algorithm>
#include <iostream>
#include <vector>

int count_even(const std::vector<int>& v) {
	return std::count_if(v.begin(), v.end(),
		[](int x) { return x % 2 == 0; });
}

int main() {
	std::vector vec{ 1, 2, 3, 4, 5, 6, 7 };
	std::cout << count_even(vec) << '\n';
}
