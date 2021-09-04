#include <iostream>

void f();  // can throw whatever
void g() noexcept;  // promises not to throw

int main() {
	std::cout << std::boolalpha
	          << noexcept( 2 + 3 ) << '\n'
	          << noexcept( throw 17 ) << '\n'
	          << noexcept( f() ) << '\n'
	          << noexcept( g() ) << '\n';
}
