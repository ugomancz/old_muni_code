#include <initializer_list>
#include <iostream>

struct Example {
	Example() {
		std::cout << "no parameters\n";
	}
	Example(int x) {
		std::cout << "one parameter: " << x << '\n';
	}
	Example(int x, int y) {
		std::cout << "two parameters: " << x << ", " << y << '\n';
	}
	Example(std::initializer_list<int> list) {
		std::cout << "list of parameters: ";
		const char* sep = "";
		for (int elem : list) {
			std::cout << sep << elem;
			sep = ", ";
		}
		std::cout << '\n';
	}
};

int main() {
	Example e1;
	Example e2{};
	Example e3(7);
	Example e4{ 7 };
	Example e5(7, 11);
	Example e6{ 7, 11 };
	Example e7{ 1, 2, 3, 4, 5, 6, 7 };

	for (int i : { 1, 2, 3 }) {
		std::cout << i << '\n';
	}
}
