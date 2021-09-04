#include <algorithm>
#include <iostream>
#include <vector>

auto greater_than(int value) {
	// [&] would be an error!
	return [=](auto elem) { return elem > value; };
}

int main() {
	std::vector intvec{ 1, 2, 3, 4 };
	std::cout << std::count_if(
		intvec.begin(),
		intvec.end(),
		greater_than(3)) << '\n';

	std::vector dblvec{ 1.0, 2.1, 3.14, 4.7 };
	std::cout << std::count_if(
		dblvec.begin(),
		dblvec.end(),
		greater_than(3)) << '\n';
	}
