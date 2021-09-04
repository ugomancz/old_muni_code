#include <algorithm>
#include <iostream>
#include <vector>

int count_bigger(const std::vector<int>& v, int val) {
	return std::count_if(v.begin(), v.end(),
		[=](int x) { return x > val; });
}

int main() {
	std::vector vec{ 1, 2, 3, 4, 5, 6, 7 };
	std::cout << count_bigger(vec, 4) << '\n';
}
