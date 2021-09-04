#include <iostream>
#include <memory>

struct Animal {
	virtual void speak() const {
		std::cout << "<generic animal noise>\n";
	}

	virtual ~Animal() = default;
};

struct Dog : Animal {
	// try erasing const and/or override
	void speak() const override {
		std::cout << "Whoof!\n";
	}
};

struct Cat : Animal {
	void speak() const override {
		std::cout << "Meow!\n";
	}
};

struct NonVirtual {
	int x;
	void foo() {}
};

struct Virtual {
	int x;
	virtual void foo() {}
};

int main() {
	Dog fido;
	fido.speak();

	Animal& ref = fido;
	ref.speak();

	std::cout << sizeof(NonVirtual) << ' '
	          << sizeof(Virtual) << '\n';
}
