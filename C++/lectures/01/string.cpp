// Basic string operations

#include <iostream>
#include <string>

int main() {
	std::string s = "Hello";
	s[0] = 'J';
	std::cout << s << '\n'; // Jello

	std::string t;
	t = s;
	t[0] = 'H';
	std::cout << t << '\n'; // Hello

	s = t + ", " + "world!"; // this works
	std::cout << s << '\n'; // Hello, world!

	// s = "James" + " " + "Bond"; // this does NOT work
	s = std::string("James") + " " + "Bond"; // this works

	std::cout << s.length() << '\n'; // 10
}
