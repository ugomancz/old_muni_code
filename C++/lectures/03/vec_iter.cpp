#include <iostream>
#include <string>
#include <vector>

int main() {
	std::vector vec{ 10, 20, 30 };
	const auto& cref = vec;

	// vector<int>::iterator
	auto it = vec.begin();

	// vector<int>::const_iterator
	auto cit = cref.begin();

	std::cout << *it << '\n';  // 10
	++it;
	std::cout << *it << '\n';  // 20
	--it;
	std::cout << *it << '\n';  // 10

	it += 2;
	*it += 3;

	vec.insert(it, 17);

	for (int x : vec) {
		std::cout << x << ' ';
	}

	std::cout << '\n';
}
