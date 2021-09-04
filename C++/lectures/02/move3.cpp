#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main() {
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(std::cin, line)) {
		lines.push_back(std::move(line));
		assert(line.empty());
	}
}
