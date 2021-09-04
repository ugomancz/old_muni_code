#include <iostream>

template <typename T>
struct Base {
	T t;
};

template <typename T, typename U>
struct Derived : Base<T> {
	using Base<T>::t;
	U u;
	void run() {
		t.run();
		u.run();
	}
};

struct X {
	void run() { std::cout << "X::run\n"; }
};
struct Y {
	void run() { std::cout << "Y::run\n"; }
};

int main() {
	Derived<X, Y> d;
	d.run();
}
