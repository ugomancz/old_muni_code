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

template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { using type = T; };

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <typename T>
enable_if_t<is_pointer_v<T>> foo(T) {
	std::cout << "pointer\n";
}

template <typename T>
enable_if_t<!is_pointer_v<T>> foo(T) {
	std::cout << "non-pointer\n";
}

int main() {
	int x{};

	foo(x);
	foo(&x);
}
