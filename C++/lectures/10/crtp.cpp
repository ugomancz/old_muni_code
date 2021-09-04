#include <iostream>

template <typename T>
struct Inc {
	T& operator++() {
		T& self = static_cast<T&>(*this);
		self.inc();
		return self;
	}
	T operator++(int) {
		T& self = static_cast<T&>(*this);
		auto copy(self);
		++self;
		return copy;
	}
};

class Counter : public Inc<Counter> {
	int _count = 0;

public:
	void inc() { ++_count; }
	int count() const { return _count; }
};

int main() {
	Counter c1;
	auto c2 = ++c1;
	auto c3 = c1++;

	std::cout << c1.count() << ' '
	          << c2.count() << ' '
	          << c3.count() << '\n';
}
