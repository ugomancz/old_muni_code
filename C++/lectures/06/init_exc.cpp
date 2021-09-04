#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class Logger {
	std::ofstream log;

public:
	Logger(const std::string& filename) : log(filename) {
		if (!log)
			throw std::runtime_error("Cannot open file");
	}
};

class App {
	Logger logger;

public:
	App(const std::string& log_file)
	try : logger(log_file) {
		std::cout << "App started.\n";
	} catch (std::runtime_error& ex) {
		std::cerr << "Cannot start app: " << ex.what() << '\n';
		// implicit rethrow happens here
	}
};

int main() {
	try {
		App app("");
	} catch (...) {
		std::cerr << "Something bad happened :-(\n";
	}
}
