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

Reporter r1(1);

void foo() {
	std::cout << "In foo, before static declaration.\n";
	static Reporter r_static(4);
	std::cout << "In foo, after static declaration.\n";
}

void bar(bool b) {
	std::cout << "In bar(" << std::boolalpha << b << ").\n";
	if (b) {
		static Reporter r(5);
	}
}

int main() {
	std::cout << "main() starts.\n\n";
	Reporter r2(2);
	{
		std::cout << "In nested block, before declaration.\n";
		Reporter r3(3);
		std::cout << "In nested block, after declaration.\n";
	}
	std::cout << '\n';
	foo();
	foo();
	std::cout << '\n';
	bar(false);
	bar(true);
	bar(true);
	std::cout << '\n';
	// temporary objects
	Reporter{6};
	std::cout << Reporter(7).id << '\n';

	// lifetime extension
	const auto& r8 = Reporter(8);
	auto&& r9 = Reporter(9);

	std::cout << "\nmain() ends.\n";
}
