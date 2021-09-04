#include <iostream>
#include <string>

void f(std::string& msg) {
	std::cout << msg << ": reference\n";
}

void f(const std::string& msg) {
	std::cout << msg << ": const reference\n";
}

void f(std::string&& msg) {
	std::cout << msg << ": rvalue reference\n";
}

int main() {
	std::string s1 = "mutable l-value";
	const std::string s2 = "read-only l-value";

	f(s1);
	f(s2);
	f(std::string("temporary"));
}
