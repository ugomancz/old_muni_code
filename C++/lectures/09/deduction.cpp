#include <initializer_list>

template <typename T>
void by_val(T t) {
	T::tell_me_your_type();
}

template <typename T>
void by_ref(T& t) {
	T::tell_me_your_type();
}

template <typename T>
void by_cref(const T& t) {
	T::tell_me_your_type();
}

void foo() {}

int main() {
	// by_val("hello");
	// by_ref("hello");

	// int a[] = { 1, 2, 3 };
	// by_val(a);
	// by_ref(a);

	// by_val(foo);
	// by_ref(foo);

	// by_val({ 1, 2, 3 });
	// auto il = { 1, 2, 3 };
	// il.tell_me_your_type();

	/*
	int var;
	const int answer = 42;
	*/
	/*
	by_val(var);
	by_ref(var);
	by_cref(var);
	*/
	/*
	by_val(answer);
	by_ref(answer);
	by_cref(answer);
	*/
}
