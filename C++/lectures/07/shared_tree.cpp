#include <iostream>
#include <memory>

struct Node {
	int value;
	std::shared_ptr<Node> left, right;
	std::weak_ptr<Node> parent;

	explicit Node(int v) : value(v) {
		std::cout << "Node(" << value << ") created\n";
	}

	~Node() {
		std::cout << "Node(" << value << ") destroyed\n";
	}

	void print() const {
		std::cout << "I am Node(" << value << ") and ";
		if (auto p = parent.lock()) {
			std::cout << "my parent is Node("
			          << p->value << ")\n";
		} else {
			std::cout << "I am ROOT!\n";
		}
	}
	void draw(int depth = 0) const {
		for (int i = 0; i < depth; ++i) {
			std::cout << "  ";
		}
		std::cout << value << '\n';
		if (left)
			left->draw(depth + 1);
		if (right)
			right->draw(depth + 1);
	}
};

void set_left(std::shared_ptr<Node> parent,
              std::shared_ptr<Node> child) {
	parent->left = child;
	child->parent = parent;
}
void set_right(std::shared_ptr<Node> parent,
               std::shared_ptr<Node> child) {
	parent->right = child;
	child->parent = parent;
}

std::shared_ptr<Node> make_tree() {
	std::shared_ptr<Node> nodes[5];
	for (int i = 0; i < 5; ++i) {
		nodes[i] = std::make_shared<Node>(i);
	}

	set_left(nodes[0], nodes[1]);
	set_right(nodes[0], nodes[2]);
	set_left(nodes[2], nodes[3]);
	set_right(nodes[2], nodes[4]);

	return nodes[0];
}

int main() {
	auto root = make_tree();
	root->draw();

	auto rr = root->right;

	rr->print();
	root.reset();

	rr->print();
	rr->draw();
}
