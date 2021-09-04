#include <iostream>

struct Base {
	virtual void tell() const {
		std::cout << "I am Base.\n";
	}

	Base() {
		std::cout << "Base constructor: ";
		tell();
	}

	void non_virtual() {
		std::cout << "Base non-virtual function: ";
		tell();
	}

	~Base() {
		std::cout << "Base destructor: ";
		tell();
	}
};

struct Derived : Base {
	void tell() const override {
		std::cout << "I am Derived.\n";
	}

	Derived() {
		std::cout << "Derived constructor: ";
		tell();
	}

	~Derived() {
		std::cout << "Derived destructor: ";
		tell();
	}
};

int main() {
	Derived d;
	std::cout << "---\n";
	d.non_virtual();

	std::cout << "---\n";

	Base& ref = d;
	ref.non_virtual();
	std::cout << "---\n";
}
