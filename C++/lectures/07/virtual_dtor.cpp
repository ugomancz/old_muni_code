#include <memory>
#include <vector>

class Base {
public:
	// virtual ~Base() = default;
};

class Derived : public Base {
	std::vector<int> v;
public:
	Derived() : v(1000) {}
};

int main() {
	std::unique_ptr<Base> ptr =
		std::make_unique<Derived>();
}
