#include <iostream>
#include <list>

int main() {
	std::list list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// Erasing an element from a list invalidates the iterator to
	// the erased element. Fortunately, erase returns a new (valid)
	// iterator that points to the next element.

	for (auto it = list.begin(); it != list.end(); ) {
		if (*it % 2 == 0) {
			it = list.erase(it);
		} else {
			++it;
		}
	}

	// Note: With std::list, the above code is linear w.r.t.
	// the size of the list; with std::vector it would be quadratic!
	// (See the complexity of the erase methods.)

	for (int num : list) {
		std::cout << num << ' ';
	}

	std::cout << '\n';
}
