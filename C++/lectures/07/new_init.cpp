#include <iostream>

class Thing {
	static int get_id() {
		static int id = 0;
		return id++;
	}

	int id = get_id();

public:
	Thing() { std::cout << id << " constructor\n"; }
	Thing(int x, int y) {
		std::cout << id << " constructor with arguments: "
		          << x << ", " << y << '\n';
	}
	~Thing() { std::cout << id << " destructor\n"; }
};

int main() {
	int* ptr1 = new int;    // uninitialised!
	int* ptr2 = new int(17);
	int* ptr3 = new int();  // initialised to zero

	std::cout << *ptr1 << ' '  // run valgrind
	          << *ptr2 << ' '
	          << *ptr3 << '\n';

	Thing* ptr4 = new Thing;  // calls Thing()
	Thing* ptr5 = new Thing(4, 2);

	std::cout << "---\n";
	delete ptr5;
	delete ptr4;
	delete ptr3;
	delete ptr2;
	delete ptr1;
	std::cout << "---\n";

	int* arr1 = new int[200];    // uninitialised
	int* arr2 = new int[200]();  // init. to zero

	Thing* arr3 = new Thing[10];

	std::cout << "---\n";
	delete [] arr3;
	delete [] arr2;
	delete [] arr1;
	std::cout << "---\n";
}
