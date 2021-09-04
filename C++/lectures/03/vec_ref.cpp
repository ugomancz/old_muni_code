#include <functional>
#include <iostream>
#include <string>
#include <vector>

class Person {
	std::string name;
	int age;

public:
	Person(std::string name, int age)
	    : name(name), age(age) {}

	void make_older() { ++age; }

	void print() const {
		std::cout << name << ", age: " << age << '\n';
	}
};

int main() {
	Person marge("Marge", 34);
	Person homer("Homer", 36);

	// we don't want to make a vector of *copies*
	std::vector<std::reference_wrapper<Person>> people;

	people.emplace_back(marge);
	people.emplace_back(homer);

	for (Person& person : people) {
		person.make_older();
	}

	homer.print();
}
