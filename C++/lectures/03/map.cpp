#include <iostream>
#include <map>
#include <string>

void print_map(const std::map<int, std::string>& m) {
	// const std::pair<const int, std::string>& element
	for (auto& [k, v]: m) {
		std::cout << k << ": " << v << '\n';
	}
}

int main() {
	std::map<int, std::string> cpp_teachers = {
		{ 72525, "Nikola Beneš" },
		{ 139761, "Petr Ročkai" } };

	// pre-C++11
	cpp_teachers.insert(std::make_pair(373979, "Vladimír Štill"));

	// C++11, {} initialization
	cpp_teachers.insert({ 422279, "Jan Mrázek" });

	// C++11, emplace
	cpp_teachers.emplace(410438, "Henrich Lauko");

	if (auto it = cpp_teachers.find(72525);
	    it == cpp_teachers.end()) {
		std::cout << "nenalezeno\n";
	} else {
		std::cout << "nalezeno " << it->first << ": "
			  << it->second << '\n';
		it->second += ", Ph.D.";
	}

	auto it = cpp_teachers.begin();
	++it;
	for (; it->first < 400000; ++it) {
		it->second += ", Ph.D.";
	}

	print_map(cpp_teachers);
}
