#include <algorithm>
#include <iostream>

struct Vec3D {
	int x, y, z;

	int sum() const {
		return x + y + z;
	}
	int max() const {
		return std::max(x, std::max(y, z));
	}
};

int main() {
	Vec3D a{ 0, 0, 0 };
	Vec3D b{ 1, 2, 3 };

	// since C++11, we can use auto here
	int Vec3D::* ptr = &Vec3D::x;

	auto fptr = &Vec3D::sum;

	fptr = &Vec3D::max;

	std::cout << a.*ptr << '\n';
	std::cout << b.*ptr << '\n';

	std::cout << (a.*fptr)() << '\n';
	std::cout << (b.*fptr)() << '\n';
}
