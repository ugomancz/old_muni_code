#include <iostream>
#include <optional>
#include <string_view>

std::optional<int> parse_int(std::string_view str) {
	if (str.empty())
		return {};

	bool negative = false;
	auto it = str.begin();
	if (*it == '-') {
		negative = true;
		++it;
	}
	if (it == str.end())
		return {};

	int result = 0;
	for(; it != str.end(); ++it) {
		if (*it < '0' || *it > '9')
			return {};
		result = result * 10 + *it - '0';
	}

	return negative ? -result : result;
}

int main() {
	auto x = parse_int("-42");

	std::cout << (x ? *x : -1) << '\n';

	try {
		std::cout << x.value() << '\n';
	} catch (std::bad_optional_access& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
	}

	std::cout << x.value_or(-1) << '\n';
}
