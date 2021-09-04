#include <map>
#include <cassert>
#include <cmath>
#include <set>
#include <vector>
#include <numeric>
#include <climits>

/* Basic graph and tree algorithms, 8 points. */

/* Given a non-empty tree, compute some of its properties (listed
 * below). Nodes are numbered, with root being node number 1 (do not
 * assume anything else about node numbering). A branch is a path
 * from the root to a leaf. Each edge is assigned a non-negative
 * length. The length of a branch is the sum of lengths of all its
 * edges. */

using node = int;
using length = int;
using edge = std::pair<length, node>;
using tree = std::multimap<node, edge>;

/* Ensure that the input really is a tree, i.e. that each node is
 * reachable by exactly 1 path from the root. All other functions
 * can assume that ‹is_tree› holds for their input.
 *
 * Hint: in a tree, the number of edges is the number of nodes - 1.
 * Beware though, the converse does not hold. */

bool is_tree_rec(const tree &t, std::set<node> &visited, node current_node) {
    if (visited.find(current_node) != visited.end()) { // visited already
        return false;
    }
    visited.emplace(current_node);
    for (auto &[n, e] : t) {
        if (n == current_node) {
            if (!is_tree_rec(t, visited, e.second)) {
                return false;
            }
        }
    }
    return true;
}

bool all_visited(const tree &t, std::set<node> visited) {
    for (const auto &[node, edge] : t) {
        if (visited.find(node) == visited.end()) {
            return false;
        }
    }
    return true;
}

bool is_tree(const tree &t) {
    std::set<node> visited;
    bool result = is_tree_rec(t, visited, 1);
    return all_visited(t, visited) && result;
}

/* Compute the length of the longest branch. */

int longest_branch_rec(const tree &t, int current_node, int edge_length) {
    int result = 0;
    for (auto &[n, e] : t) {
        if (n == current_node) {
            if (auto depth = longest_branch_rec(t, e.second, e.first); depth > result) {
                result = depth;
            }
        }
    }
    return result + edge_length;
}

int longest_branch(const tree &t) {
    return longest_branch_rec(t, 1, 0);
};

/* Compute the length of the shortest branch. */
int shortest_branch_rec(const tree &t, int current_node, int edge_length) {
    if (t.find(current_node) == t.end()) { // leaf reached
        return edge_length;
    }
    int result = INT_MAX;
    for (auto &[n, e] : t) {
        if (n == current_node) {
            if (auto depth = shortest_branch_rec(t, e.second, e.first); depth < result) {
                result = depth;
            }
        }
    }
    return result + edge_length;
}

int shortest_branch(const tree &t) {
    return shortest_branch_rec(t, 1, 0);
}

/* Compute the average length among all branches. */
void average_branch_rec(const tree &t, std::vector<int> &lengths, int current_node, int current_depth) {
    if (t.find(current_node) == t.end()) {
        lengths.emplace_back(current_depth);
        return;
    }
    for (auto &[n, e] : t) {
        if (n == current_node) {
            average_branch_rec(t, lengths, e.second, current_depth + e.first);
        }
    }

}

double average_branch(const tree &t) {
    std::vector<int> lengths;
    average_branch_rec(t, lengths, 1, 0);
    return static_cast<double>(std::accumulate(lengths.begin(), lengths.end(), 0)) /
           static_cast<double>(lengths.size());
}

/* What follows are «basic» test cases for your convenience. You can
 * add additional test cases into main(): they «will not» be
 * executed during evaluation, so it is okay to submit with broken
 * main. However, make sure to «not» alter the line with the
 * prototype. */

int main() {
    tree g{{1, {1, 2}},
           {1, {1, 6}},
           {2, {1, 4}},
           {2, {1, 5}},
           {6, {1, 4}}},
            h{{1, {1, 2}},
              {5, {1, 6}}},

            t{{1, {1, 2}},
              {1, {7, 6}},
              {2, {1, 4}},
              {2, {1, 5}},
              {5, {1, 77}}},
            u{{1, {1, 4}},
              {4, {1, 6}}},
            v{{1, {0, 4}},
              {1, {3, 2}}};

    assert(!is_tree(g));
    assert(!is_tree(h));
    assert(is_tree(t));
    assert(is_tree(u));
    assert(is_tree(v));

    assert(longest_branch(t) == 7);
    assert(shortest_branch(t) == 2);

    assert(longest_branch(u) == 2);
    assert(shortest_branch(u) == 2);

    assert(longest_branch(v) == 3);
    assert(shortest_branch(v) == 0);

    assert(std::fabs(average_branch(u) - 2) < 1e-6);
    assert(std::fabs(average_branch(v) - 1.5) < 1e-6);

    return 0;
}
