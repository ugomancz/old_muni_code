#include <cctype>
#include <algorithm>
#include <vector>
// #include <iostream>  // try uncommenting this line

int main() {
	std::vector v = {'A', 'B', 'C', 'D'};
	bool b;

	// note: undefined behaviour
	//       std::isalpha is not specified as addressable
	b = std::all_of(v.begin(), v.end(), std::isalpha);

	// this is OK
	b = std::all_of(v.begin(), v.end(),
		[](char c) { return std::isalpha(c); });

	return b;
}
