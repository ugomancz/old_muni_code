#include <iostream>
#include <map>
#include <string>

void print_map(const std::map<std::string, int>& m) {
	for (auto& [k, v] : m) {
		std::cout << k << ": " << v << '\n';
	}
}

int main() {
	std::map<std::string, int> names_to_uco;
	names_to_uco["Nikola Beneš"] = 72525;

	if (names_to_uco["James Bond"] == 007) {
		std::cout << "Yes\n";
	}

	print_map(names_to_uco);
}
