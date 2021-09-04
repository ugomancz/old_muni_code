#include <vector>
#include <cassert> // the assert macro (C header)

void test_vector() {
	std::vector vec0 = { 1, 2, 3 };
	std::vector vec1 = vec0;
	vec0[1] = 42;
	assert(vec0 == vec1); /* ERROR */
}

int main() {
	test_vector();
}
