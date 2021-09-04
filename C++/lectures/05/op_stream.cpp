#include <iostream>

class ChessPos {
	int _x;
	int _y;

public:
	ChessPos(int x, int y) : _x(x), _y(y) {}

	friend std::ostream& operator<<(std::ostream& out,
	                                const ChessPos& pos) {
		return out << static_cast<char>(pos._x + 'a')
		           << pos._y + 1;
	}

	friend std::istream& operator>>(std::istream& in,
	                                ChessPos& pos) {
		char cx, cy;
		if (in >> cx && cx >= 'a' && cx <= 'h' &&
		    in >> cy && cy >= '1' && cy <= '8') {
			pos._x = cx - 'a';
			pos._y = cy - '1';
		} else {
			in.setstate(std::ios::failbit);
		}
		return in;
	}
};

int main() {
	ChessPos cp(3, 5);
	std::cout << cp << '\n';
	if (std::cin >> cp) {
		std::cout << "Okay, read: " << cp << '\n';
	} else {
		std::cout << "Bad chess position.\n";
	}
}
