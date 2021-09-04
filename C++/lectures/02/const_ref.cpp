#include <iostream>

int main() {
	int a = 1;
	const int& cref = a;
	std::cout << cref << '\n';
	cref = 7; // error
}
