#include <iostream>
#include <map>
#include <string_view>

class Counter {
	std::map<char, int> _map;

public:
	explicit Counter(std::string_view sv) {
		for (char c: sv) {
			++_map[c];
		}
	}

	void print() const {
		std::cout << "{\n";
		for (auto& [key, value] : _map) {
			std::cout << "  '" << key << "': " << value << ",\n";
		}
		std::cout << "}\n";
	}

	Counter& operator+=(const Counter& other) {
		for (auto& [key, value] : other._map) {
			_map[key] += value;
		}
		return *this;
	}
};

#if 1

Counter operator+(Counter lhs, const Counter& rhs) {
	lhs += rhs;
	return lhs;
}

Counter operator+(const Counter& lhs, Counter&& rhs) {
	// luckily, our addition is commutative
	rhs += lhs;
	// std::move is needed here, because rhs is not a value argument
	return std::move(rhs);
}

#else

// an even more optimised version

Counter operator+(const Counter& lhs, const Counter& rhs) {
	auto copy = lhs;
	copy += rhs;
	// this uses NRVO, so it might not even move
	return copy;
}

Counter operator+(Counter&& lhs, const Counter& rhs) {
	lhs += rhs;
	return std::move(lhs);
}

Counter operator+(const Counter& lhs, Counter&& rhs) {
	rhs += lhs;
	return std::move(rhs);
}

Counter operator+(Counter&& lhs, Counter&& rhs) {
	lhs += rhs;
	return std::move(lhs);
}

#endif

int main() {
	Counter c1{ "Hello" };
	Counter c2{ "world!" };
	Counter c3{ "Wololo!" };
	(c1 + (c2 + c3)).print();

	// note: (c1 + (c2 + c3)) is now basically the same as:
	//   Counter tmp = c2;
	//   tmp += c3;
	//   tmp += c1;
	// i.e. only one copy is made
	// (again, some moves happen)
}
