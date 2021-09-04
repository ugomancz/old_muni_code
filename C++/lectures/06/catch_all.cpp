#include <iostream>

class SomeException {};
class OtherException {};

void handle_exception() {
	try {
		throw;
	} catch (SomeException&) {
		std::cout << "SomeException\n";
	} catch (OtherException&) {
		std::cout << "OtherException\n";
	}
}

void do_something() {
	throw SomeException();
}

int main() {
	try {
		do_something();
	} catch (...) {
		handle_exception();
	}
}
