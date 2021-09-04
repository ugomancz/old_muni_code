#include <iostream>

struct Reporter {
	int id;
	Reporter(int id) : id(id) {
		std::cout << "Reporter " << id << " created\n";
	}
	// this is a destructor
	// we will talk about destructors in a later lecture
	~Reporter() {
		std::cout << "Reporter " << id << " destroyed\n";
	}
};

struct Base {
	Reporter r1{ 1 };
	Base() {
		std::cout << "Base constructor\n";
	}
	~Base() {
		std::cout << "Base destructor\n";
	}
};

struct Derived : public Base {
	static Reporter r4;
	Reporter r2;
	Reporter r3;
	// note: initialisation order is based on declaration order,
	// not the order in the initialisation section!
	Derived() : r2(2), r3(3) {
		std::cout << "Derived constructor\n";
	}
	~Derived() {
		std::cout << "Derived destructor\n";
	}
};

Reporter Derived::r4{ 4 };

int main() {
	std::cout << "-- main starts\n";
	{
		std::cout << "-- block starts\n";
		Derived d;
		std::cout << "-- block ends\n";
	}
	std::cout << "-- main ends\n";
}
