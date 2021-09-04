#include <iostream>
#include <string>
#include <variant>

struct Rock {};
struct Paper {};
struct Scissors {};

using Play = std::variant<Rock, Paper, Scissors>;

struct Eval {
	template <typename T>
	int operator()(T, T) { return 0; }

	int operator()(Rock, Scissors) { return 1; }
	int operator()(Scissors, Paper) { return 1; }
	int operator()(Paper, Rock) { return 1; }

	template <typename T, typename U>
	int operator()(T, U) { return -1; }
};

Play choose() {
	std::cout << "Choose R, S, P: ";
	std::string line;
	while (std::getline(std::cin, line)) {
		switch (line[0]) {
		case 'R':
		case 'r':
			return Rock{};
		case 'P':
		case 'p':
			return Paper{};
		case 'S':
		case 's':
			return Scissors{};
		}
	}
	throw std::runtime_error("Input ended.");
}

int main() {
	auto p1 = choose();
	auto p2 = choose();
	int result = std::visit(Eval(), p1, p2);

	switch (result) {
	case 1:
		std::cout << "First player wins.\n";
		break;
	case 0:
		std::cout << "Tie!\n";
		break;
	case -1:
		std::cout << "Second player wins.\n";
		break;
	}
}
