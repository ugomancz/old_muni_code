#include <iostream>

int main() {
	int a = 1;
	int b = 2;

	int* ptr = &a;
	ptr = &b;   // try commenting out
	// *ptr = b;  // try uncommenting

	*ptr += 7;
	// ptr += 7;  // what happens now?

	std::cout << a << ", " << b << '\n';

	int& ref = a;
	ref = b;   // is this like ptr = &b or *ptr = b?

	ref += 7;  // is this like ptr += 7 or *ptr += 7?

	std::cout << a << ", " << b << '\n';
}
