#include <iostream>

class X {
	int id;

public:
	explicit X(int id) : id(id) { std::cout << "X(" << id << ")\n"; }
	~X() { std::cout << "~X() with id = " << id << '\n'; }
};

class YBase {
public:
	YBase() { std::cout << "YBase constructor\n"; }
	~YBase() { std::cout << "YBase destructor\n"; }
};

class Y : public YBase {
	X x;
	int id;

public:
	Y(int x, int id) : x(x), id(id) {
		std::cout << "Y constructor\n";
		if (id < 0)
			throw std::runtime_error("negative id");
	}

	~Y() {
		std::cout << "Y destructor\n";
	}
};

void g() {
	X x(3);
	Y y(4, -1);
	throw std::runtime_error("no reason at all");
}

void f() {
	X x(2);
	g();
}

int main() {
	X x(0);
	try {
		X x1(1);
		f();
		X x42(42);
	} catch (std::runtime_error& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
	}
}
