#include <iostream>

template <typename T, std::size_t N>
void print_array(const T (&array)[N]) {
	std::cout << N << " elements: {";
	const char* sep = "";
	for (const T& elem : array) {
		std::cout << sep << elem;
		sep = ", ";
	}
	std::cout << "}\n";
}

int main() {
	int array[] = { 1, 1, 2, 3, 5, 8 };

	print_array(array);
}
