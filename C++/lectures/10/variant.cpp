#include <iostream>
#include <string>
#include <variant>

int main() {
	std::variant<int, std::string, double> v = 3.14;
	std::cout << v.index() << '\n';
	std::cout << std::holds_alternative<int>(v) << '\n';
	try {
		std::cout << std::get<2>(v) << '\n';
		std::cout << std::get<double>(v) << '\n';
	} catch (std::bad_variant_access& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
	}

	if (auto* ptr = std::get_if<double>(&v)) {
		std::cout << "got double: " << *ptr << '\n';
	} else {
		std::cout << "not double\n";
	}
}
