#include <set>
#include <iostream>

int main() {
	std::set s = { 1, 3, 3, 7, 0, 42, -17 };

	if (auto it = s.find(17); it != s.end()) {
		std::cout << "Found: " << *it << ".\n";
	} else {
		std::cout << "Not found.\n";
	}

	std::cout << *s.begin() << '\n';

	auto it = s.end();
	--it;
	--it;
	std::cout << *it << '\n';

	s.erase(--s.end()); // remove largest element

	if (auto [it, inserted] = s.insert(42); inserted) {
		std::cout << "Inserted: " << *it << '\n';
	} else {
		std::cout << "Already present.\n";
	}

	for (int x : s) {
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
