#include <iostream>
#include <memory>
#include <vector>

struct Dog {
	void speak() const {
		std::cout << "Whoof!\n";
	}
};

struct Cat {
	void speak() const {
		std::cout << "Meow!\n";
	}
};

struct Person {
	std::string _name;
	Person(std::string name) : _name(std::move(name)) {}
	void speak() const {
		std::cout << "Hello, my name is " << _name << ".\n";
	}
};

struct SConcept {
	virtual void speak() const = 0;
	virtual ~SConcept() = default;
	virtual std::unique_ptr<SConcept> clone() const = 0;
};

template <typename T>
struct SModel : SConcept {
	T _object;
	explicit SModel(T object) : _object(std::move(object)) {}

	void speak() const override {
		_object.speak();
	}
	std::unique_ptr<SConcept> clone() const override {
		return std::make_unique<SModel>(_object);
	}
};

class Speaker {
	std::unique_ptr<SConcept> _ptr;
public:
	template <typename T>
	explicit Speaker(T object)
	  : _ptr(std::make_unique<SModel<T>>
	         (std::move(object))) {}

	void speak() const { _ptr->speak(); }

	Speaker(const Speaker& other)
	  : _ptr(other._ptr->clone()) {}
	Speaker& operator=(const Speaker& other) {
		_ptr = other._ptr->clone();
		return *this;
	}

	Speaker(Speaker&&) = default;
	Speaker& operator=(Speaker&&) = default;
	~Speaker() = default;
};

int main() {
	std::vector<Speaker> speakers;

	speakers.emplace_back(Dog());
	speakers.emplace_back(Cat());
	speakers.emplace_back(Person("Ro Laren"));

	auto clone = speakers;

	for (auto& speaker: clone) {
		speaker.speak();
	}
}
