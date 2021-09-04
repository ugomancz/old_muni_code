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

inline  // if this were in a header file
Counter operator+(Counter lhs, const Counter& rhs) {
	lhs += rhs;
	return lhs;
	// note: don't do the following, it makes another copy!
	//   return lhs += rhs;
}

int main() {
	Counter c1{ "Hello" };
	Counter c2{ "world!" };
	Counter c3{ "Wololo!" };
	(c1 + c2 + c3).print();

	// note: (c1 + c2 + c3) is basically the same as:
	//   Counter tmp = c1;
	//   tmp += c2;
	//   tmp += c3;
	// i.e. only one copy is made
	// (some moves are made as well, but the Counter objects
	//  are cheap to move)
}
