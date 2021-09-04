#include <memory>
#include <iostream>

struct X {
	X() { std::cout << "X constructed\n"; }
	~X() { std::cout << "X destroyed\n"; }
};

struct Node {
	X value;
	std::shared_ptr<Node> next;
};

int main() {
	auto n1 = std::make_shared<Node>();
	auto n2 = std::make_shared<Node>();
	n1->next = n2;
	n2->next = n1;
}
