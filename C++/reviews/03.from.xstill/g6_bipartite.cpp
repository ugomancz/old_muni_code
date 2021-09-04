#include <map>
#include <vector>
#include <cassert>
#include <queue>
#include <algorithm>

using edges = std::vector< int >;
using graph = std::map< int, edges >;

/** enum class by byl asi lepší… a typicky se v C++ moc nepoužívají názvy jen z
 ** velkých písmen pro věci co nejsou makra **/
/** drobnost: NONE bych dal první, aby měl číselnou hodnotu 0 **/
enum color {
    RED, BLUE, NONE
};

color opposite_color(color color) {
    assert(color != NONE);
    return color == RED ? BLUE : RED;
}

/* Check whether a given graph is bipartite. The graph is undirected, i.e. its
 * adjacency relation is symmetric. */
bool is_bipartite(const graph &g) {
    if (!g.empty()) {
        std::vector<color> colored(g.size() + 1, NONE);
        std::queue<int> q;
        q.push(1);
        colored.at(1) = RED;
        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            if (std::find(g.at(vertex).begin(), g.at(vertex).end(), vertex) !=
                g.at(vertex).end()) { // reflexivity detected
                return false;
            }
            for (const auto neighbour : g.at(vertex)) {
                if (colored.at(vertex) == colored.at(neighbour)) { // neighbour has same color
                    return false;
                } else if (colored.at(neighbour) == NONE) { // neighbour hasn't been visited yet
                    colored.at(neighbour) = opposite_color(colored.at(vertex));
                    q.push(neighbour);
                }
            }
        }
    }
    return true;
}

int main()
{
    assert(  is_bipartite( graph() ) );
    assert(  is_bipartite( graph{ { 1, {} } } ) );
    assert(  is_bipartite( graph{ { 1, { 2 } }, { 2, { 1 } } } ) );
    assert(  is_bipartite( graph{ { 1, {} }, { 2, {} } } ) );

    graph g{ { 1, { 2, 3 } }, { 2, { 1, 3 } }, { 3, { 1, 2 } } };
    assert( !is_bipartite( g ) );

    graph h{ { 1, { 2 } }, { 2, { 1, 3 } }, { 3, { 2 } } };
    assert( is_bipartite( h ) );

    graph i{ { 1, { 2, 3 } }, { 2, { 1 } }, { 3, { 1 } } };
    assert( is_bipartite( i ) );

    graph j{ { -1, { -2 } }, { -2, { -1 } },
             { 1, { 2, 3 } }, { 2, { 1, 3 } }, { 3, { 1, 2 } } };
    assert( !is_bipartite( j ) );
}
