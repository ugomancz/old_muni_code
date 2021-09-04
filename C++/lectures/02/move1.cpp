#include <vector>
#include <string>
#include <cassert>

int main() {
	std::vector vec1{ 1, 2, 3, 4, 5 };
	std::vector vec2 = std::move(vec1);

	assert(vec1.empty());
	assert(vec2.size() == 5);
}
