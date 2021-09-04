#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>
#include <vector>
#include <map>

struct basic_tag {};
struct string_tag {};
struct sequence_tag {};
struct assoc_tag {};

template <typename T>
struct pprint_kind { using tag = basic_tag; };

template <>
struct pprint_kind<std::string> { using tag = string_tag; };

template <>
struct pprint_kind<std::string_view> { using tag = string_tag; };

template <typename T>
struct pprint_kind<std::vector<T>> { using tag = sequence_tag; };

template <typename K, typename V>
struct pprint_kind<std::map<K, V>> { using tag = assoc_tag; };

template <typename T>
void pprint(const T& value) {
	pprint_impl(value, typename pprint_kind<T>::tag{});
}

template <typename T>
void pprint_impl(const T& value, basic_tag) {
	std::cout << value;
}

template <typename T>
void pprint_impl(const T& str, string_tag) {
	std::cout << std::quoted(str);
}

template <typename T>
void pprint_impl(const T& seq, sequence_tag) {
	const char* sep = "[ ";
	for (const auto& elem : seq) {
		std::cout << sep;
		pprint(elem);
		sep = ", ";
	}
	std::cout << " ]";
}

template <typename T>
void pprint_impl(const T& assoc, assoc_tag) {
	const char* sep = "{ ";
	for (const auto& [key, value] : assoc) {
		std::cout << sep;
		pprint(key);
		std::cout << ": ";
		pprint(value);
		sep = ",\n  ";
	}
	std::cout << " }";
}

int main() {
	std::vector<std::string> v{ "One", "Two", "Three" };
	pprint(v);
	std::cout << '\n';

	std::map<std::string, std::vector<int>> m{
		{ "James Bond", { 0, 0, 7 } },
		{ "THX", { 1, 1, 3, 7 } },
	};
	pprint(m);
	std::cout << '\n';
}
