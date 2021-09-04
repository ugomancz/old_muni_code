#include <iostream>
#include <string>

class Person {
	std::string _name;
	int _age;

public:
	Person(const std::string& name, int age)
	  : _name(name), _age(age) {
		std::cout << "New Person created: "
		          << _name << '\n';
	}

	void rename(const std::string& new_name) {
		_name = new_name;
	}

	int age() const;

	void say_hello() const {
		std::cout << _name << " (age "
		          << _age << ") says hello!\n";
	};
};

int Person::age() const {
	return _age;
}

int average_age(const Person& a, const Person& b) {
	// we cannot do this:
	// a.rename("HAHAHAHA");

	return (a.age() + b.age()) / 2;
}

int main() {
	Person rick{ "Rick Sanchez", 70 };
	Person morty("Morty Smith", 14);

	rick.say_hello();

	std::cout << average_age(rick, morty) << '\n';

	std::cout << Person("Jerry Smith", 34).age() << '\n';
}
