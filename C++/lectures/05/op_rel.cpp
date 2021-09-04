#include <iostream>
#include <set>
#include <string>

struct Person {
	std::string name, surname;

	Person(std::string name, std::string surname)
	  : name(std::move(name)), surname(std::move(surname)) {}

	void print() const {
		std::cout << name << ' ' << surname << '\n';
	}

	friend bool operator==(const Person& lhs, const Person& rhs) {
		return lhs.name == rhs.name && lhs.surname == rhs.surname;
	}

	friend bool operator<(const Person& lhs, const Person& rhs) {
		if (lhs.surname < rhs.surname)
			return true;
		if (rhs.surname < lhs.surname)
			return false;
		return lhs.name < rhs.name;
	}

/*
	// C++ 20
	friend std::strong_ordering operator<=>(const Person& lhs,
			                        const Person& rhs) {
		if (auto cmp = lhs.surname <=> rhs.surname; cmp != 0)
			return cmp;
		return lhs.name <=> rhs.name;
	}

	// https://en.cppreference.com/w/cpp/language/default_comparisons
*/
};

inline bool operator!=(const Person& lhs, const Person& rhs) {
	return !(lhs == rhs);
}
inline bool operator>=(const Person& lhs, const Person& rhs) {
	return !(lhs < rhs);
}
inline bool operator>(const Person& lhs, const Person& rhs) {
	return rhs < lhs;
}
inline bool operator<=(const Person& lhs, const Person& rhs) {
	return !(rhs < lhs);
}

int main() {
	std::set<Person> people = {
		{ "Paul", "Atreides" },
		{ "Vladimir", "Harkonnen" },
		{ "Duncan", "Idaho" },
		{ "Leto", "Atreides" },
	};

	for (const auto& person : people) {
		person.print();
	}
}
