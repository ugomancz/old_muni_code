// Various kinds of initialisation

#include <iostream>
#include <string>

struct Init {
	int w;
	int x;
	int y{};
	int z = 42;
	std::string s;
	std::string t;
	std::string u{};
	std::string v = "foo";

	Init() : x(7), t("bar") { }

	void dump() {
		std::cout << "w = " << w
		          << ", x = " << x
		          << ", y = " << y
		          << ", z = " << z
		          << ", s = \"" << s
		          << "\", t = \"" << t
		          << "\", u = \"" << u
		          << "\", v = \"" << v
		          << "\"\n";
	}
};

int main() {
	Init x;
	x.dump();
}
