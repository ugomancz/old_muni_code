#include <iostream>

int main() {
	int* ptr = new int;
	int* array = new int[100];

	delete [] array;
	delete ptr;

	bool p;

	std::cin >> p;
	int* guess_what = p ? new int : new int[100];

	delete [] guess_what;
}
