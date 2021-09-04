#include <algorithm>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <map>
#include <type_traits>

// see 10/crtp.cpp
template <typename T>
class IncDec {
	T& _self() { return static_cast<T&>(*this); }
public:
	T& operator++() {
		T& self = _self();
		self.inc();
		return self;
	}
	T operator++(int) {
		T& self = _self();
		auto copy(self);
		++self;
		return copy;
	}
	T& operator--() {
		T& self = _self();
		self.dec();
		return self;
	}
	T operator--(int) {
		T& self = _self();
		auto copy(self);
		--self;
		return copy;
	}
};

template <typename MapIt>
class ValueIterator : public IncDec<ValueIterator<MapIt>> {
	MapIt _it;

	using _value = typename MapIt::value_type::second_type;
	using _cvalue = std::conditional_t<
		std::is_const_v<
			std::remove_reference_t<typename MapIt::reference>
		>, const _value, _value>;
public:
	ValueIterator() = default;
	ValueIterator(MapIt it) : _it(it) {}

	using value_type = _value;
	using difference_type = typename MapIt::difference_type;
	using reference = _cvalue&;
	using pointer = _cvalue*;
	using iterator_category = std::bidirectional_iterator_tag;

	void inc() { ++_it; }
	void dec() { --_it; }

	reference operator*() const { return _it->second; }
	pointer operator->() const { return &_it->second; }

	friend bool operator==(const ValueIterator& a, const ValueIterator& b) {
		return a._it == b._it;
	}
	friend bool operator!=(const ValueIterator& a, const ValueIterator& b) {
		return !(a == b);
	}
};

int main() {
	std::map<int, char> roman{
		{1, 'i'}, {5, 'v'}, {10, 'x'}, {50, 'l'},
		{100, 'c'}, {500, 'd'}, {1000, 'm'},
	};

	std::transform(
		ValueIterator(roman.cbegin()),
		ValueIterator(roman.cend()),
		ValueIterator(roman.begin()),
		[](char c) { return std::toupper(c); }
	);

	for (auto& [k, v] : roman) {
		std::cout << std::setw(4) << k << ": " << v << '\n';
	}
}
