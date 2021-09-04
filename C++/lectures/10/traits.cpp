#include <iostream>

template <typename T>
struct is_pointer {
	static inline const bool value = false;
};

template <typename T>
struct is_pointer<T*> {
	static inline const bool value = true;
};

template <typename T>
const bool is_pointer_v = is_pointer<T>::value;

int main() {
	std::cout << is_pointer_v<int> << ' '
	          << is_pointer_v<int*> << ' '
	          << is_pointer_v<int&> << ' '
	          << is_pointer_v<const int*> << '\n';
}
