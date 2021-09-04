#include <iostream>
#include <string>

class Label {
	std::string _letters = "A";

public:
	Label& operator++() {
		auto it = _letters.begin();
		while (it != _letters.end() && *it == 'Z') {
			*it = 'A';
			++it;
		}
		if (it == _letters.end()) {
			_letters.push_back('A');
		} else {
			++*it;
		}
		return *this;
	}

	Label operator++(int) {
		auto copy(*this);
		++*this;
		return copy;
	}

	void print() const {
		for (auto it = _letters.rbegin(); it != _letters.rend(); ++it) {
			std::cout << *it;
		}
		std::cout << '\n';
	}
};

int main() {
	Label lbl;
	for (int i = 0; i < 16383; ++i) {
		++lbl;
	}
	lbl.print();
	auto old = lbl++;
	lbl.print();
	old.print();
}
