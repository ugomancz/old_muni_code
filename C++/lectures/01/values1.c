// This is C, not C++
#include <stdio.h>

struct Point {
	int x, y;
};

void foo(struct Point p) {
	p.x = 7;
}

int main() {
	struct Point a = { 1, 2 };
	struct Point b = a;
	foo(b);
	a.y = 9;
	printf("a = { %d, %d }; b = { %d, %d };\n",
	       a.x, a.y, b.x, b.y);
}
