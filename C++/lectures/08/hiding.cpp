#include <iostream>

class Base {
	int value = 1;
public:
	void fun_a() const {
		std::cout << "Base::fun_a " << value << '\n';
	}

	void fun_b() const {
		std::cout << "Base::fun_b " << value << '\n';
	}
};

class Derived : public Base {
	int value = 2;
public:
	void fun_b(int x) {
		std::cout << "Derived::fun_b " << value << ' ' << x << '\n';
	}
};

int main() {
	Derived d;
	d.fun_a();

	// error: fun_b() is hidden
	// d.fun_b();

	d.fun_b(7);

	d.Base::fun_b();
}
