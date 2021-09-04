#include <iostream>
#include <string>

void print_word(std::string_view word) {
	std::cout << "Word: " << word << '\n';
}

void parse_words(std::string_view text) {
	// no new std::strings are created here
	auto start = text.find_first_not_of(' ');
	while (start != std::string_view::npos) {
		auto end = text.find_first_of(' ', start);
		print_word(text.substr(start, end - start));
		start = text.find_first_not_of(' ', end);
	}
}

int main() {
	using namespace std::string_literals;

	auto ptr = "This is a C string.";
	auto str = "This is an std::string."s;

	// ptr.tell_type();
	// str.tell_type();

	std::string s1 = "The end.\0After the end.";
	std::string s2 = "The end.\0After the end."s;

	std::cout << s1.length() << " \"" << s1 << "\"\n";
	std::cout << s2.length() << " \"" << s2 << "\"\n";

	parse_words("There are some words here.");
}
