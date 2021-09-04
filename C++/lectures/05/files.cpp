#include <fstream>
#include <iostream>

int main() {
	{
		std::ofstream out("message.txt");
		out << "ZHOFRPH WR JUDYLWB IDOOV!\n";
		// the file is closed at the end of current block
	}
	{
		std::string line;
		std::ifstream in("message.txt");
		while (std::getline(in, line)) {
			std::cout << line << '\n';
		}
	}
}
