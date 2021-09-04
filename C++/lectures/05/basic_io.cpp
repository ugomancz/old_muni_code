#include <iostream>
#include <string>

int main() {
	int i;
	double d;
	std::string s;
	std::cin >> i >> d >> s;
	std::cout << i << ' ' << d << ' ' << s << '\n';
	// note that << has higher priority than ==
	std::cout << (i == d) << '\n';
}
