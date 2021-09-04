#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>

// see 10/crtp.cpp
template <typename T>
struct Inc {
	T& operator++() {
		T& self = static_cast<T&>(*this);
		self.inc();
		return self;
	}
	T operator++(int) {
		T& self = static_cast<T&>(*this);
		auto copy(self);
		++self;
		return copy;
	}
};

template <typename T>
class LinkedList {
	class Node {
		T value;
		std::unique_ptr<Node> next;
		friend LinkedList;
	public:
		Node(const T& value) : value(value) {}
		Node(T&& value) : value(std::move(value)) {}
	};

	std::unique_ptr<Node> first;

	template <typename CNode, typename CValue>
	class Iterator : public Inc<Iterator<CNode, CValue>> {
		CNode* node = nullptr;
	public:
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using reference = CValue&;
		using pointer = CValue*;
		using iterator_category = std::forward_iterator_tag;

		Iterator() = default;

		// allow implicit casting from iterator to const_iterator
		template <typename CN, typename CV>
		Iterator(const Iterator<CN, CV>& other) : node(other.node) {}

		friend bool operator==(Iterator a, Iterator b) {
			return a.node == b.node;
		}
		friend bool operator!=(Iterator a, Iterator b) {
			return !(a == b);
		}

		reference operator*() const { return node->value; }
		pointer operator->() const { return &node->value; }

		void inc() {
			node = node->next.get();
		}

	private:
		Iterator(CNode* node) : node(node) {}

		friend LinkedList;
	};

public:
	using iterator = Iterator<Node, T>;
	using const_iterator = Iterator<const Node, const T>;

	LinkedList() = default;
	~LinkedList() = default;

	LinkedList(const LinkedList& other) {
		const Node* node = other.first.get();
		auto* store = &first;
		while (node) {
			*store = std::make_unique<Node>(node->value);
			store = &*store->next;
			node = node->next;
		}
	}
	LinkedList(LinkedList&&) = default;
	LinkedList& operator=(LinkedList other) {
		using std::swap;
		swap(first, other.first);
	}

	bool empty() const { return first == nullptr; }

	void push_front(const T& value) {
		_push_front(value);
	}
	void push_front(T&& value) {
		_push_front(std::move(value));
	}

	iterator begin() { return { first.get() }; }
	const_iterator begin() const { return { first.get() }; }
	const_iterator cbegin() const { return { first.get() }; }

	iterator end() { return {}; }
	const_iterator end() const { return {}; }
	const_iterator cend() const { return {}; }

private:
	template <typename U>
	void _push_front(U&& value) {
		auto tail = std::move(first);
		first = std::make_unique<Node>(std::forward<U>(value));
		first->next = std::move(tail);
	}
};

int main() {
	LinkedList<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);

	std::copy(list.begin(), list.end(),
		  std::ostream_iterator<int>(std::cout, "\n"));
}
