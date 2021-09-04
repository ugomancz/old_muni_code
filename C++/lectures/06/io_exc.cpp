#include <fstream>
#include <iostream>

int main() {
	try {
		std::ifstream in("data.txt");
		in.exceptions(in.failbit);
		std::cout << "---\n";
		int num;
		in >> num;
		std::cout << "Got num: " << num << '\n';
	} catch (std::ios_base::failure& ex) {
		std::cerr << "I/O Error: " << ex.what() << '\n';
	}
}
