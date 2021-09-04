// Value semantics of C++ (copies)

#include <iostream>
#include <vector>

// try the following variants:
// void f(std::vector<int>& v) {
// void f(const std::vector<int>& v) {
void foo(std::vector<int> v) {
	v.push_back(17);
	// try this:
	// std::vector<int> w = { 1, 2, 3 };
	// v = w;
}

int main() {
	std::vector<int> x = { 7, 8, 9 };
	std::vector<int> y = x;
	foo(y);
	x[0] = 23;

	for (int a : y) {
		std::cout << a << ' ';
	}
	std::cout << '\n';
}
