#include <functional>
#include <iostream>
#include <string>
#include <vector>

class Person {
	std::string _name;
	unsigned _salary = 0;

public:
	Person(std::string name) : _name(std::move(name)) {}
	const std::string& name() const { return _name; }
	void tell() const { std::cout << _name << ": " << _salary << "\n"; }

	friend void rename_person(Person& p,
			          std::string name);
	friend class Employer;
};

void rename_person(Person& p, std::string name) {
	p._name = std::move(name);
}

class Employer {
	std::vector<std::reference_wrapper<Person>> employees;

public:
	void addEmployee(Person& person) {
		employees.emplace_back(person);
	}
	void raiseAll() {
		for (Person& employee : employees) {
			employee._salary += 1;
		}
	}
};

int main() {
	Person edric("Edric");
	rename_person(edric, "Edric the Navigator");
	Employer guild;
	guild.addEmployee(edric);
	guild.raiseAll();
	edric.tell();
}
