#include <iostream>
#include <string>
#include <tuple>
#include <utility>

void show1() {
	std::pair<int, int> point;

	point.first = 10;
	point.second = 17;

	std::cout << point.first << ", " << point.second << '\n';

	std::tuple<bool, int, std::string> answer;

	std::get<0>(answer) = true;
	std::get<1>(answer) = 42;
	std::get<2>(answer) = "Yes";

	const auto& [b, i, s] = answer;
	std::cout << std::boolalpha << b << ", " << i << ", " << s << '\n';
}

void show2() {
	std::pair<int, int> point(10, 17);
	auto [x, y] = point;  // copies
	std::cout << x << ", " << y << '\n';

	std::tuple<bool, int, std::string> answer =
		{ true, 42, "Yes" };
	auto& [b, i, s] = answer;  // references
	i += 1;

	std::cout << std::get<1>(answer) << '\n';

	bool yes_no;
	int number;
	std::string message;

	std::tie(yes_no, number, message) = answer;

	int y_value;

	std::tie(std::ignore, y_value) = point;

	std::cout << message << ", " << y_value << '\n';
}

void print_ids_tuple(const std::tuple<int, double, std::string>& t) {
	std::cout << std::get<0>(t) << ", "
	          << std::get<1>(t) << ", "
	          << std::get<2>(t) << '\n';
}

void show3() {
	std::pair agent("James Bond", 007);
	std::tuple nums(1, 1ull, 1.0, 1.f);

	// we can abuse compiler errors to tell us the type
	// agent.tell_me_the_type_please();

	agent = std::make_pair("James Bond", 007);
	nums = std::make_tuple(1, 1ull, 1.0, 1.f);

	print_ids_tuple({ 3, 3.14, "Pie" });
}

int main() {
	show1();
	show2();
	show3();
}
