#include <any>
#include <string>
#include <iostream>

struct Thing {
	Thing() { std::cout << "Thing constructed\n"; }
	Thing(const Thing&) { std::cout << "Thing copied\n"; }
	Thing(Thing&&) noexcept { std::cout << "Thing moved\n"; }
	Thing& operator=(const Thing&) {
		std::cout << "Thing copy-assigned\n";
		return *this;
	}
	Thing& operator=(Thing&&) noexcept {
		std::cout << "Thing move-assigned\n";
		return *this;
	}
	~Thing() { std::cout << "Thing destroyed\n"; }
};

int main() {
	std::any a = std::string("Nightfall");

	try {
		std::cout << std::any_cast<int>(a) << '\n';
	} catch (std::bad_any_cast& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
	}

	// pointer version
	if (auto* ptr = std::any_cast<int>(&a)) {
		std::cout << "got int: " << *ptr << '\n';
	} else {
		std::cout << "not int\n";
	}

	std::cout << "---\n";
	// created, then moved
	std::any a1 = Thing();
	std::cout << "---\n";
	a1.reset();
	std::cout << "---\n";

	// created directly
	std::any a2 = std::make_any<Thing>();

	std::cout << "--- copy:\n";
	auto t1 = std::any_cast<Thing>(a2);

	std::cout << "--- reference:\n";
	auto& ref = std::any_cast<Thing&>(a2);

	std::cout << "--- move:\n";
	auto t2 = std::any_cast<Thing&&>(std::move(a2));

	std::cout << "--- copy any\n";
	auto clone = a2;

	std::cout << "--- move any\n";
	auto moved = std::move(a2);
	// try removing noexcept from move constructor

	std::cout << "---\n";
}
