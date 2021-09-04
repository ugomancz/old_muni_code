#include <vector>
#include <iostream>

struct Device {
	std::string name;
	std::vector<int> part_numbers;
};


void print_device(const Device& device) {
	std::cout << "device name: " << device.name
	          << ", part numbers: ";
	const char* sep = "";
	for (int part_no : device.part_numbers) {
		std::cout << sep << part_no;
		sep = ", ";
	}
	std::cout << '\n';
}

int main() {
	Device ls;
	ls.name = "Lightsaber";
	ls.part_numbers = { 1138, 327 };
	Device ls_deluxe = ls;
	ls_deluxe.name += " DeLuxe";
	ls_deluxe.part_numbers.push_back(1729);

	print_device(ls);
	print_device(ls_deluxe);
}
