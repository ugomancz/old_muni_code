#include <iostream>

void by_val(int x) { x += 4; }
void by_ref(int& x) { x += 4; }

int main() {
	int a = 38;
	by_val(a);
	std::cout << a << '\n';
	by_ref(a);
	std::cout << a << '\n';
}
