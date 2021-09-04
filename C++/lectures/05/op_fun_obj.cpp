#include <algorithm>
#include <iostream>
#include <vector>

class Adder {  // not the snake
	int val;

public:
	Adder(int v) : val(v) {}
	int operator()(int x) const { return x + val; }
};

int main() {
	std::vector<int> v{ 1, 2, 3, 7, 10, 15 };
	std::vector<int> w;
	std::transform(v.begin(), v.end(), back_inserter(w), Adder(100));

	const char* sep = "";
	for (int x : w) {
		std::cout << sep << x;
		sep = ", ";
	}
	std::cout << '\n';
}
