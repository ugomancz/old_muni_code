int y;

template<typename T>
void f() {
	T::x * y;
}

struct A {
	using x = int;
};

struct B {
	static inline int x = 1;
};

int main() {
	// f<A>();
	f<B>();
}
