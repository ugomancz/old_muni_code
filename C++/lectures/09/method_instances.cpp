template<typename T>
struct X {
	T t;
	void f() { t.f(); }
	void g() { t.g(); }
};
class A { public: void f() {} };
int main() {
	X<A> x;   // OK
	x.f();    // OK
	// x.g(); // ERROR
	X<int> y; // OK
	// y.f(); // ERROR
}

// explicit instantiation of all methods:
// template struct X<A>;
