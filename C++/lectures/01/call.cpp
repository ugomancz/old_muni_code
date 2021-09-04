// Call by value vs. call by reference

#include <iostream>
#include <vector>

void f1(std::string s) {
	s[0] = 'X';
	s = "You won't see this.";
}

void f2(std::string& s) {
	s[0] = 'X';
	s = "You will see this.";
}

void f3(const std::string& s) {
	// this won't compile:
	// s[0] = 1;
	// s = "Cannot do this.";
	std::cout << "In f3: " << s << '\n';
}

int main() {
	std::string my_string = "This is my string.";

	f1(my_string);
	std::cout << "After f1: " << my_string << '\n';

	f2(my_string);
	std::cout << "After f2: " << my_string << '\n';

	f3(my_string);
}
