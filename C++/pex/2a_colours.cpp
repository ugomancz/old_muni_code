/* This task is worth «8 points». */

#include <set>
#include <cassert>
#include <map>
#include <queue>
#include <algorithm>

/* Write a function to compute the smallest possible number of
 * colours that can colour a given graph. A correct colouring is
 * such that no edge connects vertices with the same colour. The
 * graph is given as a set of edges. Edges are represented as pairs,
 * and if ⟦(u, v)⟧ is a part of the graph, so is ⟦(v, u)⟧. */

using graph = std::set< std::pair< int, int > >;

using edges = std::set<int>;
using adj = std::map<int, edges>;

adj to_adj(const graph &g) {
    adj result;
    for (const auto &[u, v] : g) {
        result[u].emplace(v);
    }
    return result;
}

int colours(const graph &g) {
    if (g.empty()) {
        return 0;
    }
    adj adj_g = to_adj(g);
    std::map<int, int> colors;
    std::queue<int> q;
    q.push(adj_g.begin()->first);

    while (true) {
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            int available_color = 1;
            for (const auto &neigh : adj_g[current]) {
                if (neigh != current) {
                    if (colors[neigh] == available_color) {
                        ++available_color;
                    }
                    if (colors[neigh] == 0) {
                        q.push(neigh);
                    }
                }
            }
            colors[current] = available_color;
        }
        if (colors.size() != adj_g.size()) {
            for (const auto &[key, value] : adj_g) {
                if (colors[key] == 0) {
                    q.push(key);
                }
            }
        } else {
            break;
        }
    }
    int result = std::max_element(colors.begin(), colors.end(),
                                  [=](const auto x, const auto y) { return x.second < y.second; })->second;
    return result;
}

/* What follows are «basic» test cases for your convenience. You can
 * add additional test cases into main(): they «will not» be
 * executed during evaluation, so it is okay to submit with broken
 * main. However, make sure to «not» alter the line with the
 * prototype. */

int main()
{
    graph g{ { 1, 2 }, { 2, 1 } };
    graph h{ { 1, 2 }, { 1, 3 },
             { 2, 1 }, { 3, 1 } };
    graph i{ { 1, 2 }, { 1, 3 }, { 2, 3 },
             { 2, 1 }, { 3, 1 }, { 3, 2 } };
    graph j{ { 1, 2 }, { 1, 3 }, { 1, 4 }, { 2, 3 }, { 2, 4 }, { 3, 4 },
             { 2, 1 }, { 3, 1 }, { 4, 1 }, { 3, 2 }, { 4, 2 }, { 4, 3 } };
    graph k{ { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 1 },
             { 2, 1 }, { 3, 2 }, { 4, 3 }, { 1, 4 } };
    graph l{ { 1, 2 }, { 3, 4 }, { 4, 5 }, { 3, 5 },
             { 2, 1 }, { 4, 3 }, { 5, 4 }, { 5, 3 } };

    assert( colours( g ) == 2 );
    assert( colours( h ) == 2 );
    assert( colours( i ) == 3 );
    assert( colours( j ) == 4 );
    assert( colours( k ) == 2 );
    assert( colours( l ) == 3 );

    return 0;
}
