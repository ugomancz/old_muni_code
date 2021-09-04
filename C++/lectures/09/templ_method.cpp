#include <iostream>

class Printer {
	std::ostream& _out;
public:
	explicit Printer(std::ostream& out) : _out(out) {}

	template <typename T>
	void print(const T& obj) const {
		_out << obj << '\n';
	}
};

int main() {
	Printer p(std::cout);
	p.print(42);
	p.print(3.14);
	p.print("Hello");
}
