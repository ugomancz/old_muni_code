#include <iostream>

int x = 42;

template< typename T >
struct A : T {
	void f() { std::cout << x << '\n'; }
	void g() { std::cout << this->x << '\n'; }
};

struct X { int x = 17; };
struct Y {};

int main() {
	A<Y> ay;
	A<X> ax;
	ay.f(); ax.f(); ax.g();
}
