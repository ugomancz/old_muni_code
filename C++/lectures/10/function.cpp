#include <functional>
#include <iostream>
#include <vector>

struct X {
	int value;

	int get() const { return value; }
};

int get(const X& x) { return x.value; }

int main() {
	int c = 0;
	std::vector<std::function<int(const X&)>> vec;

	vec.emplace_back(get);
	vec.emplace_back([](const auto& x) {
		return x.value;
	});
	vec.emplace_back([&c](const auto& x) {
		return x.value + c++;
	});
	vec.emplace_back(&X::get);
	vec.emplace_back(&X::value);

	X x{ 42 };
	for (auto& f : vec) {
		std::cout << f(x) << '\n';
	}
	std::cout << c << '\n';
}
