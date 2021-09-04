/* Another exercise for graph exploration, this time we will look
 * for cycles. There are a few algorithms to choose from, those
 * based on DFS are probably the most straightforward. */

#include <map>
#include <cassert>

/* This time, the input graph is given as a «multimap»: a map which
 * can contain multiple values for each key. In other words, it
 * behaves as a set of pairs with additional support for efficient
 * retrieval based on the value of the first field of the pair. The
 * ‹is_dag› function should return ‹false› iff ‹g› contains a cycle.
 * The graph does not need to be connected. */

using graph = std::multimap< int, int >;

void dfs(const graph &g, const int vertex, std::map<int, bool> &visited, std::map<int, int> &departure, int &time) {
    visited[vertex] = true;
    for (auto pair : g) {
        if (pair.first == vertex && !visited[pair.second]) {
            dfs(g, pair.second, visited, departure, time);
        }
    }
    departure[vertex] = time++;
}

bool is_dag(const graph &g) {
    std::map<int, bool> visited;
    std::map<int, int> departure;
    int time = 0;
    for (auto pair : g) {
        if (!visited[pair.first]) {
            dfs(g, pair.first, visited, departure, time);
        }
    }
    for (auto pair : g) {
        if (departure[pair.first] <= departure[pair.second]) {
            return false;
        }
    }
    return true;
}

int main()
{
    assert(  is_dag( graph{ { 1, 2 } } ) );
    assert( !is_dag( graph{ { 1, 1 } } ) );
    assert(  is_dag( graph{ { 1, 2 }, { 1, 3 }, { 2, 3 } } ) );

    graph g{ { 1, 2 }, { 1, 3 }, { 2, 4 }, { 2, 5 }, { 3, 4 } };
    assert( is_dag( g ) );

    graph h{ { 1, 2 }, { 1, 3 }, { 2, 4 }, { 2, 5 }, { 5, 1 } };
    assert( !is_dag( h ) );
}
