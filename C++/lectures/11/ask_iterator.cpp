#include <iostream>
#include <numeric>
#include <vector>

// see 10/crtp.cpp
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

class AskUserIterator : public Inc<AskUserIterator> {
	int value = 0;

public:
	using value_type = int;
	using difference_type = std::ptrdiff_t;
	using reference = int;
	using pointer = const int*;
	using iterator_category = std::input_iterator_tag;

	void inc() {
		std::cout << "Give me a number please (0 to end): ";
		value = 0;
		std::cin >> value;
	}

	reference operator*() const { return value; }

	friend bool operator==(AskUserIterator a, AskUserIterator b) {
		return a.value == b.value;
	}
	friend bool operator!=(AskUserIterator a, AskUserIterator b) {
		return a.value != b.value;
	}

	static AskUserIterator start() {
		AskUserIterator aui;
		aui.inc();
		return aui;
	}

	static AskUserIterator stop() { return {}; }
private:
	AskUserIterator() = default;
};

int main() {
	std::cout << "Let's fill a vector.\n";
	std::vector vec(AskUserIterator::start(), AskUserIterator::stop());

	std::cout << "Vector: ";
	for (int x : vec) {
		std::cout << x << ' ';
	}
	std::cout << "\n\nLet's sum some numbers.\n";

	int total = std::accumulate(AskUserIterator::start(),
	                            AskUserIterator::stop(), 0);
	std::cout << "The sum is " << total << ".\n";
}
