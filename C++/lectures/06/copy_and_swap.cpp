#include <cassert>
#include <iostream>
#include <vector>

class Resource {
	// we shall use -1 to represent «no resource held»
	int id;

public:
	explicit Resource(int id = -1) : id(id) {
		report("acquired");
	}

	Resource(const Resource& other) : id(100 + other.id) {
		report("copied", &other);
	}

	Resource(Resource&& other) noexcept : id(other.id) {
		other.id = -1;
		report("moved", &other);
	}

	Resource& operator=(Resource other) {
		swap(other);
		return *this;
	}

	~Resource() {
		std::cout << this << " destructor\n";
		release();
	}

	bool holds_resource() {
		return id != -1;
	}

	void swap(Resource& other) {
		std::cout << this << " and " << &other
		          << " swapping resources "
		          << id << " and " << other.id << '\n';
		using std::swap;
		swap(id, other.id);
	}

private:
	void report(std::string_view msg, const Resource* from = nullptr) {
		if (id == -1)
			return;
		std::cout << this << ' ' << msg << " resource id " << id;
		if (from)
			std::cout << " from " << from;
		std::cout << '\n';
	}

	void release() {
		report("released");
		id = -1;
	}

};

void swap(Resource& a, Resource& b) {
	a.swap(b);
}

struct ResourceHolder {
	Resource something{ 17 };
	Resource other_thing{ 42 };
	Resource super_thing{ 1337 };
};

int main() {
	Resource r1(1);
	std::cout << "---\n";
	Resource r2 = r1;
	std::cout << "---\n";
	Resource r3 = std::move(r1);
	std::cout << "---\n";

	r3 = r2;
	std::cout << "---\n";
	r3 = Resource(0);  // temporary
	std::cout << "---\n";

	std::vector<Resource> vr;
	for (int i = 2; i < 7; ++i) {
		std::cout << "---" << i << "---\n";
		vr.emplace_back(i);
	}
	std::cout << "---\n";
	ResourceHolder rh;
	std::cout << "---\n";
}
