#include <algorithm>
#include <iostream>
#include <vector>

void print_vec(const std::vector<int>& vec) {
	std::cout << "{ ";
	const char* sep = "";
	for (int num : vec) {
		std::cout << sep << num;
		sep = ", ";
	}
	std::cout << " }\n";
}

int main() {
	// try this with strings instead to see that the elements
	// are actually moved
	std::vector vec{ 0, 1, 0, 4, 0, 2, 0, 5, 0 };

	print_vec(vec);

	auto it = std::remove(vec.begin(), vec.end(), 0);

	print_vec(vec);

	vec.erase(it, vec.end());

	print_vec(vec);

	vec.erase(std::remove_if(vec.begin(), vec.end(),
	            [](int num) { return num % 2 == 0; }),
	          vec.end());

	print_vec(vec);
}
