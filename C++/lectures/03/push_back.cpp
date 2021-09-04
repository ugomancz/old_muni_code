#include <iostream>
#include <string>
#include <vector>

class Person {
	std::string name;
	int age;

public:
	Person(std::string name, int age)
	    : name(std::move(name)), age(age) {}

	void print() const {
		std::cout << name << ", age: " << age << '\n';
	}
};

int main() {
	std::vector<Person> people;

	people.push_back(Person("Marge", 34));

	// C++11 initialisation
	people.push_back({ "Lisa", 8 });

	// C++11 emplace
	people.emplace_back("Bart", 10);

	std::vector<std::string> my_strings;
	my_strings.emplace_back();  // ???

	for (const auto& person : people) {
		person.print();
	}

	for (const auto& s : my_strings) {
		std::cout << '"' << s << "\"\n";
	}
}
