#include <iostream>
#include <string>

class Car {
	std::string _manufacturer;
	unsigned _door_count;

public:
	Car(std::string m, int d)
	  : _manufacturer(std::move(m)), _door_count(d) {}

	Car(int d) : Car("N/A", d) {}

	void print() const {
		std::cout << "Manufacturer: " << _manufacturer
		          << "\nDoor count: " << _door_count << "\n";
	}
};

int main() {
	Car model_s("Tesla", 5);
	Car vehicle(3);

	model_s.print();
	vehicle.print();
}
