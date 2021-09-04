// Copies vs. references in range-based for (C++11)

#include <iostream>
#include <vector>

int main() {
	std::vector<std::string> names = { "Lojza", "Franta", "Tonda" };

	// try the following variants:
	// for (std::string& s : names) {
	// for (const std::string& s : names) {
	for (std::string s : names) {
		s[0] = 'X';
	}

	// try running clang-tidy on this file
	for (std::string s : names) {
		std::cout << s << ' ';
	}
	std::cout << '\n';
}
