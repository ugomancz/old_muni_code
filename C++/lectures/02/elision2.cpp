#include <vector>

// optional copy elision
// the copy is going to be elided in all modern compilers here

std::vector<int> create_vector() {
	const int size = 1 << 24;
	std::vector result(size, 0);
	for (int i = 0; i < size; ++i) {
		result[i] = i;
	}
	return result;
}

int main() {
	std::vector vec = create_vector();
}
