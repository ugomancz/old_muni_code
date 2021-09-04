#include <iostream>
#include <memory>

struct Node {
	int key;
	std::unique_ptr<Node> child[2];
	explicit Node(int key) : key(key) {}
};

template <typename T>
class TreeTraversal {
	void _visit(Node& node) {
		T& self = static_cast<T&>(*this);
		self.visit(node);
	}

public:
	void preorder(Node* node) {
		if (node) {
			_visit(*node);
			preorder(node->child[0].get());
			preorder(node->child[1].get());
		}
	}

	void inorder(Node* node) {
		if (node) {
			preorder(node->child[0].get());
			_visit(*node);
			preorder(node->child[1].get());
		}
	}

	void postorder(Node* node) {
		if (node) {
			preorder(node->child[0].get());
			preorder(node->child[1].get());
			_visit(*node);
		}
	}
};

struct TreePrinter : TreeTraversal<TreePrinter> {
	void visit(Node& node) {
		std::cout << node.key << '\n';
	}
};

int main() {
	Node root(42);
	root.child[0] = std::make_unique<Node>(17);
	root.child[1] = std::make_unique<Node>(420);

	TreePrinter().inorder(&root);
}
