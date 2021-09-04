// Basic vector operations

#include <iostream>
#include <vector>

int main() {
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.pop_back();
	v[1] = -1;

	for (int x : v) { // C++11
		std::cout << x << '\n';
	}
}
