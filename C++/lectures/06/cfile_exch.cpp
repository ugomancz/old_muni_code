#include <cstdio>
#include <string>
#include <utility>
#include <vector>

// note: this is just an example of using RAII
// it is much better to use <iostream> for I/O purposes in C++

class CFile {
	std::FILE* ptr;

public:
	CFile(const char* filename, const char* mode)
	  : ptr(std::fopen(filename, mode)) {}

	bool is_open() const { return ptr != nullptr; }

	// no copying ...
	CFile(const CFile&) = delete;
	CFile& operator=(const CFile&) = delete;

	// ... but moving makes sense here
	CFile(CFile&& other) noexcept
	  : ptr(std::exchange(other.ptr, nullptr)) {}

	CFile& operator=(CFile&& other) noexcept {
		close();
		ptr = std::exchange(other.ptr, nullptr);
		return *this;
	}

	~CFile() { close(); }

	void close() {
		if (ptr != nullptr) {
			std::fclose(ptr);
			ptr = nullptr;
		}
	}

	size_t read(void* buffer, size_t size, size_t count) {
		return fread(buffer, size, count, ptr);
	}

	size_t write(const void* buffer, size_t size, size_t count) {
		return fwrite(buffer, size, count, ptr);
	}
};

int main() {
	std::vector<CFile> outputs;
	
	char name[] = "msgX.txt";

	// vector reallocation is OK, we have move constructor!
	for (int i = 0; i < 10; ++i) {
		name[3] = '0' + i;
		outputs.emplace_back(name, "w");
	}

	for (auto& file : outputs) {
		if (file.is_open())
			file.write("Hello!\n", sizeof(char), 7);
	}
}
