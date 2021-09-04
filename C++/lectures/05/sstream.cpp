#include <iostream>
#include <sstream>

int main() {
	std::ostringstream out;
	out << "PI = " << 3.14 << '\n';
	auto s = out.str();
	std::cout << s << '\n';

	std::istringstream in("X = 1");
	std::string var, dummy;
	int value;
	in >> var >> dummy >> value;
	std::cout << var << " = " << value << '\n';

	std::string line;
	while (std::getline(std::cin, line)) {
		std::istringstream in(line);
		std::string w;
		while (in >> w) {
			std::cout << "word: " << w << '\n';
		}
		std::cout << "--- next line ---\n";
	}
}
