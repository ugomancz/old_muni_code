#include <vector>

// (since C++17 mandatory) copy elision

std::vector<int> create_vector() {
	return std::vector(1 << 24, 42);
}

int main() {
	// try commenting out one of the two parts
	// and compare their times and allocation counts (try valgrind)
	std::vector vec = create_vector();

	std::vector orig(1 << 24, 42);
	std::vector clone = orig;
}
