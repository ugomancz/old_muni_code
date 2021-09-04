#include <iostream>
#include <string>

void f(int x, int y = 10, std::string msg = "Msg") {
	std::cout << msg << ": x = " << x << ", y = " << y << '\n';
}

int main() {
	f(1);
	f(1, 2);
	f(1, 2, "This just in");
}
