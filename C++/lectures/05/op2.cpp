#include <iostream>

class Vector3D {
	double x, y, z;

public:
	Vector3D(double x, double y, double z)
	  : x(x), y(y), z(z) {}

	void print() const {
		std::cout << '(' << x << ", " << y << ", " << z << ")\n";
	}

	// notice the lack of symmetry
	Vector3D operator+(const Vector3D& other) const {
		return { x + other.x, y + other.y, z + other.z };
	}
};

int main() {
	Vector3D u(1, 2, 3);
	Vector3D v(0, 0, 7);
	(u + v).print();
}
