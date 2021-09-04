#include <iostream>
#include <memory>

class Thing {
	int id;
public:
	explicit Thing(int id) : id(id) {
		std::cout << id << " created\n";
	}
	~Thing() {
		std::cout << id << " destroyed\n";
	}

	// no copies, no moves
	Thing(const Thing&) = delete;
	Thing(Thing&&) = delete;
	Thing& operator=(const Thing&) = delete;
	Thing& operator=(Thing&&) = delete;

	void do_something() const {
		std::cout << id << " doing something...\n";
	}
};

void run(const Thing& thing) {
	thing.do_something();
}

void run_with_ptr(const Thing* ptr) {
	if (ptr) {
		ptr->do_something();
	} else {
		std::cout << "pointer is null\n";
	}
}

int main() {
	std::cout << "before inner block\n";
	{
		// pre-C++14, prefer the new version
		// std::unique_ptr<Thing> ptr(new Thing(7));

		// C++14
		auto ptr = std::make_unique<Thing>(17);
		std::cout << "inside inner block\n";

		ptr->do_something();
		run(*ptr);

		std::cout << "still inside inner block\n";
	}
	std::cout << "after inner block\n";

	auto ptr1 = std::make_unique<Thing>(1);
	auto ptr2 = std::make_unique<Thing>(2);

	std::cout << "before move\n";
	ptr1 = std::move(ptr2);
	ptr1->do_something();
	if (ptr2 == nullptr) {
		std::cout << "ptr2 is null\n";
	}
	std::cout << "after move\n";
	ptr1.reset();
	std::cout << "after reset\n";

	auto ptr3 = std::make_unique<Thing>(3);
	run_with_ptr(ptr3.get());
	ptr3 = nullptr;
	run_with_ptr(ptr3.get());

	std::cout << "end of main\n";
}
