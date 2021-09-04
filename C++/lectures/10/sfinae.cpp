#include <iostream>

struct X {
	using tag_a = void;
};

struct Y {
	using tag_b = void;
};

struct Z {
	using tag_a = void;
	using tag_b = void;
};

struct W {};

template <typename T>
typename T::tag_a foo(T) {
	std::cout << "has tag_a\n";
}

template <typename T>
typename T::tag_b foo(T) {
	std::cout << "has tag_b\n";
}

int main() {
	X x;
	Y y;
	Z z;
	W w;
	foo(x);
	foo(y);
	// foo(z);  // ambiguous
	// foo(w);  // no matching function
}
