#include <vector>

// current gcc does not elide the copy here

std::vector<int> create_vector(bool flag) {
	const int size = 1 << 24;
	std::vector result1(size, 0);
	std::vector result2{1, 2, 3, 4};
	for (int i = 0; i < size; ++i) {
		result1[i] = i;
	}
	return flag ? result1 : result2;
}

int main() {
	std::vector vec = create_vector(true);
}
