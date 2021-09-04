#include <iostream>

struct A {
	int x;
	A(int x) : x(x) {}
};

struct B : A {
	int y;
	B(int x, int y): A(x), y(y) {}
};

int main() {
	B b1{ 1, 2 };
	B b2{ 3, 4 };
	A& ref = b1;
	ref = b2;
	std::cout << b1.x << ' ' << b1.y << '\n';
}
