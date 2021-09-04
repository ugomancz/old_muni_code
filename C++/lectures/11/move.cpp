#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string_view>
#include <vector>

template <typename V>
void show_vector(const V& v, std::string_view name) {
	std::cout << "--- " << name << " ---\n";
	for (const auto& s: v) {
		std::cout << std::quoted(s) << '\n';
	}
}

int main() {
	std::vector<std::string> v{
		"just", "some", "strings"
	};
	std::vector<std::string> w{ "here", "are" };

	w.insert(
		w.end(),
		std::move_iterator(v.begin()),
		std::move_iterator(v.end())
	);

	show_vector(v, "v");
	show_vector(w, "w");
}
