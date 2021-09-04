// This is how std::advance may be implemented.

#include <forward_list>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <vector>

template <class It, class N>
void advance_impl(It& it, N n, std::input_iterator_tag) {
	std::cout << "Using input iterator version.\n";
	while (n --> 0) { ++it; }
}

template <class It, class N>
void advance_impl(It& it, N n, std::bidirectional_iterator_tag) {
	std::cout << "Using bidirectional iterator version.\n";
	while (n > 0) { ++it; --n; }
	while (n < 0) { --it; ++n; }
}

template <class It, class N>
void advance_impl(It& it, N n, std::random_access_iterator_tag) {
	std::cout << "Using random-access iterator version.\n";
	it += n;
}

// Note: We cannot use the name ‹advance› here as that would conflict
// with ADL (argument-dependent lookup).
template <class It, class Distance>
void my_advance(It& it, Distance n) {
	using diff = typename std::iterator_traits<It>::difference_type;
	using tag = typename std::iterator_traits<It>::iterator_category;
	advance_impl(it, static_cast<diff>(n), tag{});
}

template <typename It, typename Distance>
void show_advance(std::string_view name, It iter, Distance n) {
	std::cout << name << ":\n";
	my_advance(iter, n);
	std::cout << *iter << "\n\n";
}

int main() {
	std::istringstream in("1 2 3 4 5 6 7");
	show_advance("istream_iterator", std::istream_iterator<int>(in), 4);

	std::forward_list slist{ 1, 2, 3, 4, 5, 6, 7 };
	show_advance("forward_list::iterator", slist.begin(), 4);

	std::set my_set{ 7, 6, 5, 4, 3, 2, 1 };
	show_advance("set::iterator +", my_set.begin(), 4);
	show_advance("set::iterator -", my_set.end(), -4);

	std::vector vec{ 1, 2, 3, 4, 5, 6, 7 };
	show_advance("vector::iterator +", vec.begin(), 4);
	show_advance("vector::iterator -", vec.end(), -4);
}
