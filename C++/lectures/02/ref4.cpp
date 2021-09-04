#include <iostream>

int& bad_ref() {
	int x = 10;
	return x;
}

struct Example {
	int x;

	Example(int x) : x(x) {}

	int& good_ref() {
		return x;
	}
};

int& bad_ref_again() {
	Example ex(20);
	return ex.good_ref();
}

int main() {
	std::cout << bad_ref() << '\n'; // BAD

	Example ex(17);
	std::cout << ex.good_ref() << '\n';
	int& ref = ex.good_ref();
	ref += 100;
	std::cout << ex.x << '\n';

	std::cout << bad_ref_again() << '\n'; // BAD
}
