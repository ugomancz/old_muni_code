#include <iostream>
#include <memory>

class Thing {
	int id = -1;
public:
	Thing() = default;
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

int main() {
	// not recommended
	// prefer using std::vector or std::array

	auto things = std::make_unique<Thing[]>(3);

	auto ints = std::make_unique<int[]>(10);

	// no problem here, everything is zero-initialised
	std::cout << ints[0] << '\n';
}
