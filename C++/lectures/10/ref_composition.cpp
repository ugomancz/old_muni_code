#include <type_traits>
#include <iostream>

using lv_ref = int&;
using rv_ref = int&&;

using lv_lv = lv_ref&;   // int&
using rv_lv = rv_ref&;   // int&
using lv_rv = lv_ref&&;  // int&
using rv_rv = rv_ref&&;  // int&&

int main() {
	std::cout << std::is_lvalue_reference_v<lv_lv> << '\n'
	          << std::is_lvalue_reference_v<lv_rv> << '\n'
	          << std::is_lvalue_reference_v<rv_lv> << '\n'
	          << std::is_lvalue_reference_v<rv_rv> << '\n'
	          << "---\n"
	          << std::is_rvalue_reference_v<lv_lv> << '\n'
	          << std::is_rvalue_reference_v<lv_rv> << '\n'
	          << std::is_rvalue_reference_v<rv_lv> << '\n'
	          << std::is_rvalue_reference_v<rv_rv> << '\n';
}
