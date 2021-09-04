#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

int main() {
	std::string line;
	std::getline(std::cin, line);
	std::istringstream in(line);

	std::vector<int> vec;
	std::copy(std::istream_iterator<int>(in),
	          {},  // std::istream_iterator<int>()
		  std::back_inserter(vec));

	std::cout << "---\n";
	std::transform(vec.begin(), vec.end(),
	               std::ostream_iterator<int>(std::cout, ", "),
		       [](int x) { return 2 * x; });
	std::cout << '\n';
}
