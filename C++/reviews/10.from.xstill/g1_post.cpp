/* The goal of this exercise is simple: take an oriented graph as
 * the input and produce a list (vector) of vertices in the
 * ‘leftmost’ DFS post-order. That is, visit the successors of a
 * vertex in order, starting from leftmost (different exploration
 * order will result in different post-orders). The graph is encoded
 * as a neighbourhood list. */

#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <algorithm>

template<typename value_t>
using graph = std::map<value_t, std::vector<value_t> >;

template<typename graph_t, typename value_t>
void
dfs_post_rec(const graph_t &g, const value_t &current_node, std::set<value_t> &visited, std::vector<value_t> &path) {
    visited.emplace(current_node);
    for (const auto &neighbour_node : g.at(current_node)) {
        /** find ze set je výrazně rychlejší než std::find, ten má smysl jen
         ** tam, kde .find neexistuje **/
        if (std::find(visited.begin(), visited.end(), neighbour_node) == visited.end()) {
            dfs_post_rec(g, neighbour_node, visited, path);
        }
    }
    path.emplace_back(current_node);
}

/* Construct the post-order of ‹g› starting from vertex ‹i›. */
template<typename graph_t, typename value_t>
std::vector<value_t> dfs_post(const graph_t &g, const value_t &i) {
    std::set<value_t> visited;
    std::vector<value_t> path;
    dfs_post_rec(g, i, visited, path);
    return path;
}

int main()
{
    graph< int > gi{ { 1, { 2, 3, 4 } },
                     { 2, { 1, 2 } },
                     { 3, { 3, 4 } },
                     { 4, {} },
                     { 5, { 3 } } };

    auto o = []( auto... v ) { return std::vector< int >{ v... }; };
    assert( dfs_post( gi, 5 ) == o( 4, 3, 5 ) );
    assert( dfs_post( gi, 2 ) == o( 4, 3, 1, 2 ) );
    assert( dfs_post( gi, 1 ) == o( 2, 4, 3, 1 ) );

    using color = std::tuple< short, short, short >;
    color red( 255, 0, 0 ), green( 0, 255, 0 ), blue( 0, 0, 255 ),
          yellow( 255, 255, 0 ), purple( 255, 0, 255 );

    graph< color > gc{ { red, { blue, green, yellow } },
                       { blue, { red, blue } },
                       { green, { green, yellow } },
                       { yellow, {} },
                       { purple, { green } } };

    std::vector ygp{ yellow, green, purple };
    std::vector ygrb{ yellow, green, red, blue };
    std::vector bygr{ blue, yellow, green, red };

    assert( dfs_post( gc, purple ) == ygp );
    assert( dfs_post( gc, blue ) == ygrb );
    assert( dfs_post( gc, red ) == bygr );
}
