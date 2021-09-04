#include <iostream>

int main() {
	int num;
	while (std::cin >> num) {
		std::cout << "Number: " << num << '\n';
		std::cout << "cin.good(): " << std::cin.good() << '\n'
		          << "cin.eof(): " << std::cin.eof() << '\n';
	}
	std::cout << "---\n"
	          << "cin.good(): " << std::cin.good() << '\n'
	          << "cin.eof(): " << std::cin.eof() << '\n'
	          << "cin.fail(): " << std::cin.fail() << '\n'
	          << "cin.bad(): " << std::cin.bad() << '\n';
}
