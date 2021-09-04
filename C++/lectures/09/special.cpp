#include <iostream>

template <typename T>
struct X {
	void print() const {
		std::cout << "generic version\n";
	}

	void other_print() const {
		std::cout << "generic version\n";
	}
};

template <>
struct X<int> {
	void print() const {
		std::cout << "int version\n";
	}
};

template <>
void X<double>::other_print() const {
	std::cout << "double version\n";
}

int main() {
	X<int> xi;
	X<double> xd;
	X<const char*> xccp;
	xi.print();
	xd.print();
	xccp.print();

	// xi.other_print();  // ERROR
	xd.other_print();
	xccp.other_print();
}
