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

	// no sense in using const int&
	int operator[](char c) const {
		auto it = _map.find(c);
		return it == _map.end() ? 0 : it->second;
	}

	int& operator[](char c) {
		// this creates the new value for us, yay!
		return _map[c];
	}
};

Counter operator+(Counter lhs, const Counter& rhs) {
	lhs += rhs;
	return lhs;
}

int main() {
	Counter c1{ "Hello" };
	Counter c2{ "world!" };
	Counter c3{ "Wololo!" };

	Counter c = c1 + c2 + c3;
	c['x'] = 7;

	std::cout << c['l'] << '\n';
}
