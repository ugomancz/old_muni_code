#include <iostream>

class WithId {
	// C++17
	static inline int gid = 0;

	static int next_id() {
		return gid++;
	}

	int _id;

public:
	WithId() : _id(next_id()) {}

	int id() const { return _id; }

	static int count() { return gid; }
};

// before C++17 (no inline variables):
// int WithId::gid = 0;

int main() {
	WithId w0;
	WithId w1;
	WithId w2;
	std::cout << w2.id() << '\n';
	std::cout << WithId::count() << '\n';
	std::cout << w0.count() << '\n';
}
