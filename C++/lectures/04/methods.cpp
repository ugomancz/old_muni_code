#include <iostream>

class Person {
	std::string _name;

public:
	Person(std::string name) : _name(std::move(name)) {}

	void tell_const() {
		std::cout << "non-const\n";
	}
	void tell_const() const {
		std::cout << "const\n";
	}

	void tell_ref() & {
		std::cout << "non-const lvalue\n";
	}
	void tell_ref() const & {
		std::cout << "const lvalue\n";
	}
	void tell_ref() && {
		std::cout << "rvalue\n";
	}

	std::string& name() & {
		// we return a lvalue-reference, thus allowing
		// the caller to change the attribute
		return _name;
	}

	const std::string& name() const & {
		return _name;
	}

	std::string name() && {
		// we know that the current object is an rvalue
		// (ie a temporary or a object marked using std::move)
		// returning a reference could be an error
		// (as the object is possibly going to stop existing soon)
		// but we can avoid making copies
		return std::move(_name);
	}
};

int main() {
	Person terry("Terry");
	const Person korvo("Korvo");

	Person& ref = terry;
	const Person& cref = terry;

	terry.tell_const();
	korvo.tell_const();
	ref.tell_const();
	cref.tell_const();
	Person("Jesse").tell_const();

	terry.tell_ref();
	korvo.tell_ref();
	ref.tell_ref();
	cref.tell_ref();
	Person("Yumyulack").tell_ref();
	std::move(terry).tell_ref();

	terry.name() += " from Shlorp";

	// this creates a copy
	std::string name1 = korvo.name();

	// no copies here, just a move
	std::string name2 = Person("Jesse").name();

	// a const reference
	const std::string& ref1 = korvo.name();

	// this is OK; a temporary's life is extended due to being
	// captured by a const reference (see lecture 02)
	const std::string& ref2 = Person("Yumyulack").name();

	std::cout << ref1 << ", " << ref2 << '\n';
}
