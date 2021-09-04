#include <iostream>
#include <iomanip>
#include <variant>
#include <vector>

struct PrettyPrinter {
	void operator()(const std::string& str) {
		std::cout << std::quoted(str) << '\n';
	}
	template <typename T>
	void operator()(const T& obj) {
		std::cout << obj << '\n';
	}
};

int main() {
	using Var = std::variant<int, std::string, double>;
	std::vector<Var> vec = { 3, 3.14, "3.14" };

	for (auto& v : vec) {
		std::visit([](const auto& obj) {
			std::cout << obj << '\n';
		}, v);

		std::visit(PrettyPrinter(), v);

		auto result = std::visit(
			[](const auto& obj) -> Var {
				return obj + obj;
			}, v);

		std::visit(PrettyPrinter(), result);

		std::cout << "---\n";
	}
}
