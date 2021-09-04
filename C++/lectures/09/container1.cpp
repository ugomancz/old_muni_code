#include <iostream>
#include <memory>

template <typename T>
class MyContainer {
	size_t _size;
	std::unique_ptr<T[]> _array;

public:
	explicit MyContainer(size_t s)
	  : _size(s)
	  , _array(std::make_unique<T[]>(_size)) {}

	explicit MyContainer(std::initializer_list<T> ilist)
	  : MyContainer(ilist.size()) {
		auto it = ilist.begin();
		for (size_t i = 0; i < _size; ++i) {
			_array[i] = *it++;
		}
	}

	size_t size() const { return _size; }

	const T& operator[](size_t index) const { return _array[index]; }
	T& operator[](size_t index) { return _array[index]; }
};

template <typename C>
void print(const C& container) {
	const char* sep = "";
	for (size_t i = 0; i < container.size(); ++i) {
		std::cout << sep << container[i];
		sep = ", ";
	}
	std::cout << '\n';
}

int main() {
	MyContainer<double> cont(10);

	for (size_t i = 0; i < cont.size(); ++i) {
		cont[i] = i;
	}

	print(cont);

	MyContainer deduced{ 1, 2, 3, 4 };
	print(deduced);

	// MyContainer what(10);  // ERROR
}
