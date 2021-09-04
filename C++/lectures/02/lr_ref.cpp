#include <string>

void f(const std::string& s) { /* ... */ }
void g(std::string& s) { /* ... */ }

int main() {
	std::string whatever = "XYZ";
	f("ABC");
	g("DEF");
	f(whatever);
	g(whatever);
}
