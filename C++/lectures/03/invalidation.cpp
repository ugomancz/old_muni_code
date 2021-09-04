#include <iostream>
#include <vector>

int main() {
	std::vector vec{ 1, 2, 3 };
	auto it = vec.begin();
	int& ref = vec[1];
	int* ptr = &vec[2];

	vec.push_back(4); // invalidates everything

	std::cout << *it << '\n';   // error
	std::cout << ref << '\n';   // error
	std::cout << *ptr << '\n';  // error
}
