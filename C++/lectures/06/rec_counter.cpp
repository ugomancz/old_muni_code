#include <iostream>

class RecCounter {
	static inline int count = 0;

public:
	RecCounter() { ++count; }
	~RecCounter() { --count; }

	// copying/moving does not make sense
	RecCounter(const RecCounter&) = delete;
	RecCounter(RecCounter&&) = delete;
	RecCounter& operator=(const RecCounter&) = delete;
	RecCounter& operator=(RecCounter&&) = delete;

	std::ostream& indent(std::ostream& out) const {
		for (int i = 0; i < count; ++i) {
			out << "    ";
		}
		return out;
	}
};

int fib(int x) {
	RecCounter r;
	r.indent(std::cout) << "fib(" << x << ")\n";
	return x <= 1 ? x : fib(x - 1) + fib(x - 2);
}

int main() {
	std::cout << fib(5) << '\n';
}
