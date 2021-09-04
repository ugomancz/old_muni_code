#include <iostream>
#include <string>
#include <vector>

class Person {
// try removing (or changing to private)
protected:
	std::string _name;
public:
	Person(std::string name) : _name(std::move(name)) {}

	void say_hello() const {
		std::cout << _name << " says hello.\n";
	}
};

class Teacher: public Person {
	std::vector<std::string> _courses;
public:
	Teacher(std::string name) : Person(std::move(name)) {}

	void add_course(std::string course) {
		_courses.push_back(std::move(course));
	}

	void print_courses() const {
		std::cout << _name << " teaches ";
		const char* sep = "";
		for (auto& course : _courses) {
			std::cout << sep << course;
			sep = ", ";
		}
		std::cout << ".\n";
	}
};

int main() {
	Teacher nikola("Nikola");
	nikola.add_course("PB161");
	nikola.add_course("IB002");
	nikola.print_courses();

	// this is OK, a Teacher is a Person
	Person& ref = nikola;
	ref.say_hello();

	// this is OK, but not checked by the compiler!
	// if ref were a reference to a non-Teacher Person → UB
	auto& tref = static_cast<Teacher&>(ref);
	// note that clang-tidy warns against such usage
}
