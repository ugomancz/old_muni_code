#include <algorithm>
#include <iostream>
#include <memory>

class X {
public:
	X() { std::cout << "X constructed\n"; }
	~X() { std::cout << "X destroyed\n"; }
	void non_const_m() { std::cout << "non-const method called\n"; }
	void const_m() const { std::cout << "const method called\n"; }
};

void foo1(std::unique_ptr<X> ptr) {
	// ptr is now owned by foo1
	std::cout << "in foo1\n";
	ptr->non_const_m();
	// the memory is deallocated at the end of scope here
}

void foo2(std::unique_ptr<X>&& ptr) {
	// from the caller's point of view this looks similar
	// to foo1, but the caller cannot be sure that the ownership
	// has been transferred elsewher
	auto my_ptr = std::move(ptr);
	my_ptr->non_const_m();
}

void foo3(std::unique_ptr<X>& ptr) {
	// do not do this
	std::cout << "in foo2, before reset\n";
	// foo3 can do anything with ptr, including reset and =
	ptr.reset();
	std::cout << "in foo2, after reset\n";
}

void foo4(const std::unique_ptr<X>& ptr) {
	// not recommended
	// ve cannot change ptr (via reset or =)
	// but we can change the pointed-at object
	ptr->non_const_m();
}

void foo5(const std::unique_ptr<const X>& ptr) {
	// we cannot call this with actual unique_ptr<X> argument
}

void foo6(X* ptr) {
	// we can change the pointed-at object
	ptr->non_const_m();
}

void foo7(const X* ptr) {
	// we cannot change the pointed-at object
	// ptr->nonConst();
	ptr->const_m();
}

void foo8(X& ref) {
	// we do not have to test for nullptr
	// we can change the referenced object
	ref.non_const_m();
}

void foo9(const X& ref) {
	// we do not have to test for nullptr
	// we cannot change the referenced object
	// ref.nonConst();
	ref.const_m();
}

// note: all the above functions except for foo8 and foo9 should check
// whether their parameter is nullptr
// in the case of foo8 a foo9 it is the caller's responsibility

int main() {
	auto ptr = std::make_unique<X>();

	// foo1(ptr); // does not work, we cannot copy ownership
	foo1(std::move(ptr)); // we move the ownership
	// ptr does not own anything anymore
	std::cout << "---\n";

	ptr = std::make_unique<X>();

	// foo2(ptr); // still does not work
	foo2(std::move(ptr)); // did we move the ownership or not?
	std::cout << (ptr == nullptr) << '\n';
	std::cout << "---\n";

	ptr = std::make_unique<X>();

	foo3(ptr);
	// does ptr own anything? how can we know?
	std::cout << "---\n";

	ptr = std::make_unique<X>();

	// kind-of OK, if we want to allow object modification
	// (it is needlessly complicated, however, and not recommended)
	foo4(ptr);

	std::cout << "---\n";

	// foo5(ptr); // does not work; why?

	foo6(ptr.get());

	std::cout << "---\n";

	foo7(ptr.get());

	std::cout << "---\n";

	foo8(*ptr);

	std::cout << "---\n";

	foo9(*ptr);

	std::cout << "---\n";
}
