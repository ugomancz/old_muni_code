#include <iostream>
#include <memory>

template <typename T>
class MyContainer {
	size_t _size;
	std::unique_ptr<T[]> _array;

	template <typename U>
	class Iterator {
		// a very simple iterator
		U* ptr;

	public:
		explicit Iterator(U* ptr) : ptr(ptr) {}
		friend bool operator==(const Iterator& a, const Iterator& b) {
			return a.ptr == b.ptr;
		}
		friend bool operator!=(const Iterator& a, const Iterator& b) {
			return !(a == b);
		}
		U& operator*() { return *ptr; }
		U* operator->() { return ptr; }
		Iterator& operator++() {
			++ptr;
			return *this;
		}
		Iterator operator++(int) {
			Iterator result = *this;
			++*this;
			return result;
		}
	};

public:
	using iterator = Iterator<T>;
	using const_iterator = Iterator<const T>;

	explicit MyContainer(size_t s)
	  : _size(s)
	  , _array(std::make_unique<T[]>(_size)) {}

	size_t size() const { return _size; }

	const T& operator[](size_t index) const {
		return _at(*this, index);
	}
	T& operator[](size_t index) {
		return _at(*this, index);
	}

	iterator begin() { return iterator(_array.get()); }
	iterator end() { return iterator(_array.get() + _size); }
	const_iterator begin() const { return const_iterator(_array.get()); }
	const_iterator end() const { return const_iterator(_array.get() + _size); }

private:
	template <typename Self>
	static auto& _at(Self& self, size_t index) {
		// imagine that some complex computation happens here
		return self._array[index];
	}
};

int main() {
	MyContainer<double> cont(10);
	for (size_t i = 0; i < cont.size(); ++i) {
		cont[i] = i;
	}
	for (double& d : cont) {
		std::cout << d << ' ';
		d *= 2;
	}
	std::cout << '\n';

	const auto& cref = cont;
	// cref[0] = 16;  // ERROR
	for (double d : cref) {
		std::cout << d << ' ';
	}
	// for (double& d : cref) { } // ERROR
	std::cout << '\n';
}
