#include <iostream>
#include <memory>

struct Animal {
	void speak() const {
		std::cout << "<generic animal noise>\n";
	}
};

// note: public inheritance is implicit for structs

struct Dog : Animal {
	void speak() const {
		std::cout << "Whoof!\n";
	}
};

struct Cat : Animal {
	void speak() const {
		std::cout << "Meow!\n";
	}
};

int main() {
	Dog fido;
	fido.speak();

	Animal* ptr = &fido;
	ptr->speak();

	Animal& ref = fido;
	ref.speak();

	std::unique_ptr<Animal> felix = std::make_unique<Cat>();
	felix->speak();
}
