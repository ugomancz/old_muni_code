#include <iostream>

int main() {
	int a = 1;
	int b = 2;
	int& ref = a;
	// whatever happens to ref, happens to a
	ref = b;
	ref += 7;
	std::cout << "a = " << a
	          << ", b = " << b
		  << ", ref = " << ref
		  << '\n';
}
