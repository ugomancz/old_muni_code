#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

template <typename It>
void show_iters(It from, It mid, It to) {
	using T = typename It::value_type;
	std::copy(from, mid, std::ostream_iterator<T>(std::cout, " "));
	std::cout << "| ";
	std::copy(mid, to, std::ostream_iterator<T>(std::cout, " "));
	std::cout << '\n';
}


int main() {
	std::vector v{
		3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9 };

	auto iter = std::find(v.begin(), v.end(), 6);
	auto r_iter = std::reverse_iterator(iter);

	std::cout << *iter << '\n';
	std::cout << *r_iter << '\n';

	show_iters(v.begin(), iter, v.end());
	show_iters(v.rbegin(), r_iter, v.rend());

	std::sort(v.begin(), iter);
	std::sort(v.rbegin(), r_iter);

	for (int x: v) {
		std::cout << x;
	}

	std::cout << '\n';
}
