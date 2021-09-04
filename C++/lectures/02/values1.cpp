#include <vector>
#include <iostream>

void print_vec(const std::vector<std::string>& vec) {
	std::cout << "{ ";
	const char* sep = "";
	for (const std::string& elem : vec) {
		std::cout << sep << '"' << elem << '"';
		sep = ", ";
	}
	std::cout << " }\n";
}

int main() {
	std::vector<std::string> x = { "Theta", "Eta" };
	std::vector<std::string> y = x;
	std::vector<std::string> z = { "Gamma" };

	y[1] = "Alpha";

	z.push_back("Mu");

	y = z;

	z.push_back("Epsilon");

	print_vec(y);
}
