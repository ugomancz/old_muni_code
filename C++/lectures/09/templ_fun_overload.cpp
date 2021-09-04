#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

template <typename T>
const T& max(const T& x, const T& y) {
	return x < y ? y : x;
}

template <typename T>
const T& max(const T& x, const T& y, const T& z) {
	return max(max(x, y), z);
}

template <typename T>
const T& max(const std::vector<T>& vec) {
	// assume that vec is non-empty
	return *std::max_element(vec.begin(), vec.end());
}

const char* max(const char* x, const char* y) {
	return std::strcmp(x, y) < 0 ? y : x;
}

int main() {
	std::cout << max(2.0, 3.14) << '\n';
	std::cout << max(2.0, 3.14, 42.17) << '\n';
	std::vector<unsigned> v{ 10, 40, 20, 70, 30 };
	std::cout << max(v) << '\n';

	std::cout << max(20, 70) << '\n';
	std::cout << max("ahoj", "hello") << '\n';
	std::cout << max<const char*>("ahoj", "hello")
	          << '\n';
	// ERROR
	// std::cout << max<>("ahoj", "hello") << '\n';
}
