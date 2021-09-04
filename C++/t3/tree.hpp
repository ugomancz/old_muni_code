#include <vector>
#include <memory>
#include <iostream>

/* In this task, you will write a simple tree iterator, i.e. an
 * iterator that can be used to visit all nodes of a tree, in
 * post-order. */

template<typename value_t_>
struct tree_node {
    value_t_ value;
    std::vector<std::unique_ptr<tree_node>> children;

    explicit tree_node(value_t_ value) : value(std::move(value)) {};
};

/* First, implement a ‹tree› class, with the given interface. This
 * will be the interface that ‹tree_iterator› will use (of course,
 * you can add methods and attributes to ‹tree› as you see fit, but
 * ‹tree_iterator› must not use them).
 *
 * The tree is made of nodes, where each node can have an arbitrary
 * number of children and a single value. */

template<typename value_t_>
struct tree {
    using value_t = value_t_;
    std::unique_ptr<tree_node<value_t>> _root;

    /* Substitute for any type you like, but make sure it can be
     * copied, assigned and compared for equality; again,
     * ‹tree_iterator› must not rely on the details (it can assign
     * and copy values of type ‹node_ref› though). */

    struct node_ref {
        tree_node<value_t> *node;
        tree_node<value_t> *parent = nullptr;

        node_ref(tree_node<value_t> *node, tree_node<value_t> *parent) : node(node), parent(parent) {};

        node_ref(const tree<value_t>::node_ref &other) : node(other.node), parent(other.parent) {};

        ~node_ref() = default;

        node_ref &operator=(value_t value) {
            node->value = value;
            return *this;
        }

        node_ref &operator=(const node_ref &other) {
            if (this != &other) {
                node = other.node;
            }
            return *this;
        }

        bool operator==(const node_ref &other) const {
            return node == other.node;
        }

        bool operator!=(const node_ref &other) const {
            return node != other.node;
        }

        node_ref child_at(int index) const {
            return node_ref(node->children[index].get(), node);
        }

        int child_count() const {
            return static_cast<int>(node->children.size());
        }

        const value_t &value() const {
            return node->value;
        }

        value_t &value() {
            return node->value;
        }

        node_ref add_child(const value_t &value) {
            node->children.emplace_back(std::make_unique<tree_node<value_t>>(value));
            return node_ref(node->children.back().get(), node);
        }

        tree_node<value_t> *get_parent() {
            return parent;
        }
    };

    /* These functions provide access to the tree and the values
     * stored in nodes. */

    bool empty() const {
        return !_root;
    }

    node_ref root() const {
        return node_ref(_root.get(), nullptr);
    }

    node_ref child_at(const node_ref &node, int index) const {
        return node.child_at(index);
    }

    int child_count(const node_ref &node) const {
        return node.child_count();
    }

    const value_t &value(const node_ref &node) const {
        return node.value();
    }

    value_t &value(node_ref &node) {
        return node.value();
    }

    /* Finally, methods for constructing and updating the tree
     * follow. A tree iterator must not use them. The child added
     * last has the highest index. */

    node_ref make_root(const value_t &value) {
        _root = std::make_unique<tree_node<value_t>>(value);
        return node_ref(_root.get(), nullptr);
    }

    node_ref add_child(node_ref parent, const value_t &value) {
        return parent.add_child(value);
    }

    /* Remove the entire subtree rooted at ‹node›. */

    void erase_subtree(node_ref node) {
        auto parent = node.get_parent();
        if (!parent) {
            _root.reset();
            return;
        }
        for (size_t i = 0; i < parent->children.size(); i++) {
            if (node_ref(parent->children[i].get(), nullptr) == node) {
                parent->children.erase(parent->children.begin() + i);
            }
        }
    }
};

/* Iterate a given tree in post-order; ‹tree_iterator› must be (at
 * least) a forward iterator. Adding nodes to the tree must not
 * invalidate any iterators. Removal of a node invalidates the
 * iterators pointing at that node or at any of its right siblings.
 * Dereferencing the iterator yields the «value» of the node being
 * pointed at.
 *
 * The tree given may or may not be an instance of the above class
 * template ‹tree›, but it will have a ‹node_ref› nested type and
 * the access methods (‹empty›, ‹root›, ‹child_at›, ‹child_count›
 * and ‹value›). */

/* Note: You don't have to keep the exact form of the following
 * declarations, but if you decide to replace them, you must make
 * sure that the new declarations are equivalent in this sense:
 *
 *  • it must be possible to declare values using ‹tree_iterator›
 *    and ‹const_tree_iterator› template instances as their type,
 *  • it is permissible to call ‹tree_begin› and ‹tree_end› on both
 *    ‹const› and mutable references to the respective ‹tree› type and
 *    the result type must match the below declarations. */

template<typename Iterator>
struct Increment {
    Iterator &operator++() {
        auto &self = static_cast<Iterator &>(*this);
        self.increment();
        return self;
    }

    Iterator operator++(int) {
        auto &self = static_cast<Iterator &>(*this);
        auto copy(self);
        ++self;
        return copy;
    }
};

template<typename tree>
struct tree_iterator : public Increment<tree_iterator<tree>> {
    using node = typename tree::node_ref;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename tree::value_t;
    using pointer = value_type *;
    using reference = value_type &;
private:
    tree *_tree;
    std::vector<node> stack;
public:
    tree_iterator() = default;

    tree_iterator(tree &t, std::vector<node> s) : _tree(&t), stack(s) {};

    value_type &operator*() {
        return _tree->value(stack.back());
    }

    pointer operator->() {
        return &_tree->value(stack.back());
    }

    void increment() {
        auto last = stack.back();
        stack.pop_back();
        if(!stack.empty() && _tree->child_at(stack.back(), _tree->child_count(stack.back()) - 1) == last) {
            return;
        }
        int last_index = 0;
        while(!stack.empty() && _tree->child_at(stack.back(), last_index) != last) {
            ++last_index;
        }
        ++last_index;
        if (stack.empty()) return;
        stack.emplace_back(_tree->child_at(stack.back(), last_index));
        while (_tree->child_count(stack.back()) != 0) {
            stack.emplace_back(_tree->child_at(stack.back(), 0));
        }
    }

    bool operator==(const tree_iterator<tree> &other) const {
        return _tree == other._tree && stack == other.stack;
    }

    bool operator!=(const tree_iterator<tree> &other) const {
        return _tree != other._tree || stack != other.stack;
    }
};

template<typename tree>
struct const_tree_iterator : public Increment<const_tree_iterator<tree>> {
    using node = typename tree::node_ref;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = typename tree::value_t;
    using pointer = value_type *;
    using reference = value_type &;
private:
    const tree *_tree;
    std::vector<node> stack;
public:
    const_tree_iterator() = default;

    const_tree_iterator(const tree &t, std::vector<node> s) : _tree(&t), stack(s) {};

    const value_type &operator*() const {
        return _tree->value(stack.back());
    }

    pointer operator->() const {
        return &_tree->value(stack.back());
    }

    void increment() {
        if (stack.empty()) return;
        auto last = stack.back();
        stack.pop_back();
        if(!stack.empty() && _tree->child_at(stack.back(), _tree->child_count(stack.back()) - 1) == last) {
            return;
        }
        int last_index = 0;
        while(!stack.empty() && _tree->child_at(stack.back(), last_index) != last) {
            ++last_index;
        }
        ++last_index;
        if (stack.empty()) return;
        stack.emplace_back(_tree->child_at(stack.back(), last_index));
        while (_tree->child_count(stack.back()) != 0) {
            stack.emplace_back(_tree->child_at(stack.back(), 0));
        }
    }

    bool operator==(const const_tree_iterator<tree> &other) const {
        return _tree == other._tree && stack == other.stack;
    }

    bool operator!=(const const_tree_iterator<tree> &other) const {
        return _tree != other._tree || stack != other.stack;
    }
};

template<typename tree>
tree_iterator<tree> tree_begin(tree &t) {
    if (t.empty()) {
        return tree_iterator<tree>(t, {});
    }
    std::vector<typename tree::node_ref> stack;
    auto current = t.root();
    while (t.child_count(current) > 0) {
        stack.emplace_back(std::move(current));
        current = t.child_at(current, 0);
    }
    stack.emplace_back(current);
    return tree_iterator<tree>(t, stack);
}

template<typename tree>
tree_iterator<tree> tree_end(tree &t) {
    return tree_iterator<tree>(t, {});
}

template<typename tree>
const_tree_iterator<tree> tree_begin(const tree &t) {
    if (t.empty()) {
        return const_tree_iterator<tree>(t, {});
    }
    std::vector<typename tree::node_ref> stack;
    auto current = t.root();
    while (t.child_count(current) > 0) {
        stack.emplace_back(std::move(current));
        current = t.child_at(current, 0);
    }
    stack.emplace_back(current);
    return const_tree_iterator<tree>(t, stack);
}

template<typename tree>
const_tree_iterator<tree> tree_end(const tree &t) {
    return const_tree_iterator<tree>(t, {});
}
