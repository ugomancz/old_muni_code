#include <iostream>
#include <stdexcept>

void log(std::string_view message) {
	if (message.empty()) {
		throw std::invalid_argument("empty message");
	}
	std::clog << "[LOG] " << message << '\n';
}

int main() {
	try {
		std::cout << "Before\n";
		log("");
		std::cout << "After\n";
	} catch (std::invalid_argument& ex) {
		std::cerr << "Invalid argument: "
		          << ex.what() << '\n';
	} catch (std::logic_error& ex) {
		std::cerr << "Logic error: "
		          << ex.what() << '\n';
	}
	// try switching the order of the catch blocks
	std::cout << "After try block\n";
}
