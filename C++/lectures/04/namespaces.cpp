#include <iostream>

void print() { std::cout << "::print\n"; }

namespace MyLib {
void print();

namespace Experimental {
	void print();
} // namespace Experimental

} // namespace MyLib

namespace MyLib {
class Example {
public:
	void print() const { std::cout << "MyLib::Example::print\n"; }
};
} // namespace MyLib

int main() {
	::print();
	MyLib::print();
	MyLib::Experimental::print();
	// MyLib::Example::print();
	MyLib::Example ex;
	ex.print();

	namespace MyExp = MyLib::Experimental;
	MyExp::print();

	using MyLib::print;
	print();
}

namespace MyLib {
void print() { std::cout << "MyLib::print\n"; }
namespace Experimental {
	void print() { std::cout << "MyLib::Experimental::print\n"; }
} // namespace Experimental
} // namespace MyLib
