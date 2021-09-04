#include <iostream>
#include <memory>
#include <vector>

struct Animal {
	virtual void speak() const {
		std::cout << "<generic animal noise>\n";
	}

	virtual ~Animal() = default;
};

struct Dog : Animal {
	void speak() const override {
		std::cout << "Whoof!\n";
	}
};

struct Cat : Animal {
	void speak() const override {
		std::cout << "Meow!\n";
	}

	void knock_things_down() const {
		std::cout << "Oops… Crash!\n";
	}
};

int main() {
	Cat felix;
	felix.speak();

	Animal& ref = felix;
	ref.speak();

	// use clang-tidy
	Animal animal = felix;
	animal.speak();

	std::cout << "---\n";

	std::vector<Animal> animals;
	animals.push_back(Cat());
	animals.push_back(Dog());

	for (const auto& animal : animals) {
		animal.speak();
	}

	std::cout << "---\n";

	std::vector<std::unique_ptr<Animal>> animals2;
	animals2.push_back(std::make_unique<Cat>());
	animals2.push_back(std::make_unique<Dog>());

	for (const auto& animal : animals2) {
		animal->speak();
		if (auto* cat = dynamic_cast<Cat*>(animal.get())) {
			cat->knock_things_down();
		}
	}

	std::cout << "---\n";

	try {
		auto& cat = dynamic_cast<Cat&>(animals[0]);
		cat.knock_things_down();
	} catch (std::bad_cast& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
	}
}
