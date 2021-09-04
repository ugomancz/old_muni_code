#include <iostream>

template <typename T>
struct remove_reference { using type = T; };

template <typename T>
struct remove_reference<T&> { using type = T; };

template <typename T>
struct remove_reference<T&&> { using type = T; };

template <typename T>
using remove_reference_t =
	typename remove_reference<T>::type;

int main() {
	int x = 7;
	remove_reference_t<int&> y = x;
	++y;
	std::cout << x << '\n';
}
