#include <algorithm>
#include <iostream>
#include <memory>

class Node {
	std::unique_ptr<Node> next;
	Node* prev;
	int value;

public:
	Node(std::unique_ptr<Node> n, Node* p, int v)
	    : next(std::move(n))
	    , prev(p)
	    , value(v) {}

	friend class List;

	int get() const { return value; }

	~Node() {
		// just to show when elements get deallocated
		std::cout << "destroyed: " << value << "\n";
	}
};

class List {
	std::unique_ptr<Node> first;
	Node* last = nullptr;

public:
	void append(int v) {
		auto new_last = std::make_unique<Node>(nullptr, last, v);
		if (last) {
			last->next = std::move(new_last);
			last = last->next.get();
		} else {
			first = std::move(new_last);
			last = first.get();
		}
	}

	void print() const {
		const Node* curr = first.get();
		while (curr) {
			std::cout << curr->value << ' ';
			curr = curr->next.get();
		}
		std::cout << '\n';
	}

	~List() {
		std::cout << "List destroyed\n";
	}
};

int main() {
	List list;
	for (int i : { 1, 2, 3, 4, 5 }) {
		list.append(i);
	}
	list.print();
}
