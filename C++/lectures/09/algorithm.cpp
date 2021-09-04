#include <iostream>
#include <vector>

template <typename Iter, typename Func>
void modify(Iter from, Iter to, Func func) {
	for (auto it = from; it != to; ++it) {
		*it = func(*it);
	}
}

int main() {
	std::vector vec{ 1, 1, 2, 3, 5, 8 };
	modify(vec.begin(), vec.end(),
	       [](int x) { return 2 * x + 1; });

	for (int x : vec) {
		std::cout << x << ' ';
	}
	std::cout << '\n';
}
