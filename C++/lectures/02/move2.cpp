#include <string>

class Person {
	std::string _name;

public:
	// using move
	Person(std::string name)
	    : _name(std::move(name)) {}

	// without move
	// Person(const std::string& name) : _name(name) {}
};

int main() {
	// using move: one move
	// without move: one copy
	Person rick("Rick Sanchez");

	std::string morty_name = "Morty Smith";

	// using move: one copy, one move
	// without move: one copy
	Person morty(morty_name);

	std::string jerry_name = "Jerry Smith";

	// using move: two moves
	// without move: one copy
	Person jerry(std::move(jerry_name));
}
