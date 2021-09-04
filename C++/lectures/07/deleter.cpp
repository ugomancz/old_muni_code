#include <cstdio>
#include <cstdlib>
#include <cstring>  // for POSIX strdup()
#include <iostream>
#include <memory>

struct FreeDeleter {
	void operator()(void* ptr) {
		std::cout << "Freeing memory at " << ptr << '\n';
		std::free(ptr);
	}
};

struct FileCloser {
	void operator()(FILE* file) {
		std::cout << "File closed\n";
		std::fclose(file);
	}
};

// consider using type aliases
using CFile = std::unique_ptr<FILE, FileCloser>;

int main() {
	std::unique_ptr<char[], FreeDeleter>
		s1{ strdup("lbh ybfg gur tnzr\n") };

	std::unique_ptr<FILE, FileCloser>
		f1{ std::fopen("message1.txt", "w") };

	std::fputs(s1.get(), f1.get());

	std::unique_ptr<char[], void(*)(void*)>
		s2{ strdup("blf olhg gsv tznv\n"), std::free };

	std::unique_ptr<FILE, int(*)(FILE*)>
		f2{ std::fopen("message2.txt", "w"),
		    std::fclose };

	std::fputs(s2.get(), f2.get());

	std::cout << sizeof(s1) << ' ' << sizeof(f1) << ' '
	          << sizeof(s2) << ' ' << sizeof(f2) << '\n';

}
