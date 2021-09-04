#include <iostream>
#include <memory>

struct X {
	X() { std::cout << "X created\n"; }
	~X() { std::cout << "X destroyed\n"; }
	void do_something() {
		std::cout << "X does something\n";
	}
};

int main() {
	std::weak_ptr<X> wp;
	{
		auto sp = std::make_shared<X>();
		std::cout << "inner block\n";
		wp = sp;

		// we cannot do this:
		// wp->do_something();

		if (auto ptr = wp.lock()) {
			ptr->do_something();
		}
	}

	if (auto ptr = wp.lock()) {
		ptr->do_something();
	} else {
		std::cout << "The weak pointer has expired.\n";
	}
}
