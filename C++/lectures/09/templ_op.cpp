#include <algorithm>
#include <iostream>
#include <vector>

class Printer {
	std::ostream& _out;
public:
	explicit Printer(std::ostream& out) : _out(out) {}

	template <typename T>
	void operator()(const T& obj) const {
		_out << obj << '\n';
	}
};

// this is basically equivalent:
auto printer(std::ostream& out) {
	return [&out](const auto& obj) {
		out << obj << '\n';
	};
}


int main() {
	std::vector vec{ 1, 2, 3, 4 };
	std::for_each(vec.begin(), vec.end(),
	              Printer(std::cout));
	std::for_each(vec.begin(), vec.end(),
	              printer(std::cout));
}
