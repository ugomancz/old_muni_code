#include <iostream>

void foo(int num) {
	std::cout << "foo with num = " << num << '\n';
}

void bar(int num) {
	std::cout << "bar with num = " << num << '\n';
}

int main() {
	// classic
	void (*ptr1)(int) = foo;

	ptr1(7);

	// C++11
	// (* is not needed due to implicit decay)
	auto* ptr2 = bar;

	ptr2(11);

	// & is not needed here (due to implicit decay)
	ptr2 = &foo;

	ptr2(17);
}
