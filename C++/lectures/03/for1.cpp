#include <iostream>
#include <vector>

int main() {
	std::vector vec{ 1, 3, 3, 7 };

	// pre-C++11 standard way of iterating through a vector
	for (std::vector<int>::iterator it = vec.begin();
	     it != vec.end(); ++it) {
		std::cout << *it << ' ';
		*it += 17;
	}

	std::cout << '\n';

	// since C++11 we prefer range-for if possible
	for (int& num : vec) {
		std::cout << num << ' ';
		num += 17;
	}

	std::cout << '\n';

	for (int num : vec) {
		std::cout << num << ' ';
	}

	std::cout << '\n';
}
