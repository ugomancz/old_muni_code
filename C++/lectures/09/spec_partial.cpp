#include <iostream>
#include <set>
#include <vector>

template <typename T, typename U>
struct X {
	void print() const {
		std::cout << "T, U\n";
	}
};

template <typename T>
struct X<T, double> {
	void print() const {
		std::cout << "T, double\n";
	}
};

template <typename T>
struct X<T, T> {
	void print() const {
		std::cout << "T, T\n";
	}
};

template <typename T>
struct X<int, T> {
	void print() const {
		std::cout << "int, T\n";
	}
};

template <typename Q>
struct X<Q*, const Q&> {
	void print() const {
		std::cout << "Q*, Q&\n";
	}
};

template <typename T>
struct X<std::vector<T>, std::set<T>> {
	void print() const {
		std::cout << "std::vector<T>, std::set<T>\n";
	}
};

int main() {
	X<double, char> x1;
	X<char, double> x2;
	X<char, char> x3;
	X<int, char> x4;
	// X<int, int> x5; // ERROR

	X<int*, const int&> x6;
	X<std::vector<int>, std::set<int>> x7;
	X<std::vector<int>, std::set<unsigned>> x8;

	x1.print();
	x2.print();
	x3.print();
	x4.print();

	x6.print();
	x7.print();
	x8.print();
}
