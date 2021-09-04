/* This exercise is worth «8 points». */

#include <map>
#include <vector>
#include <algorithm>

/* Implement function ‹hamilton› which takes a single non-empty
 * directed graph and returns true iff the graph contains a
 * Hamiltonian cycle, that is, a cycle that visits each vertex
 * exactly once. It is okay to use a brute-force search. The input
 * graph is given as an std::map from vertices (integers) to a list
 * of edges: */

using edges = std::vector< int >;
using graph = std::map< int, edges >;

/* The set of vertices is exactly the set of keys in the above map.
 * The graph is ill-formed if a successor of a vertex does not
 * appear as a key in the map. */

bool hamilton_rec(const graph &g, std::vector<int> &visited, int current) {
    if (!visited.empty() && std::find(visited.begin(), visited.end(), current) != visited.end()) { // already visited current vertex
        return (visited[0] == current && visited.size() == g.size());

    }
    visited.emplace_back(current);
    for (auto &neigh : g.at(current)){
        if (hamilton_rec(g,visited,neigh)) {
            return true;
        }
    }
    visited.pop_back();
    return false;
}

bool hamilton(const graph &g) {
    std::vector<int> visited;
    auto first = (g.begin())->first;
    bool result = hamilton_rec(g, visited, first);
    return result;
}

/* Here are a few hints:
 *
 *  • if there is a Hamiltonian path in the graph, it visits each
 *    vertex: it does not matter from which vertex you start your
 *    search,
 *  • it is okay to use recursion (and it is in fact a good idea):
 *    a path which does not revisit any vertices can be completed to
 *    a Hamiltonian cycle iff at least one of the outgoing edges of
 *    the last vertex on the path either a) completes a Hamiltonian
 *    cycle, or b) extends the path to a new path which does not
 *    revisit any vertices and also can be completed to a
 *    Hamiltonian cycle. */

#include <cassert>

/* What follows are «basic» test cases for your convenience. You can
 * add additional test cases into main(): they «will not» be
 * executed during evaluation, so it is okay to submit with broken
 * main. However, make sure to «not» alter the line with the
 * prototype. */

int main()
{
    graph g{ { 1, { 2 } }, { 2, {} } };
    graph h{ { 1, { 2 } }, { 2, { 1 } } };
    graph i{ { 1, { 2 } }, { 2, { 3, 1 } }, { 3, {} } };
    graph j{ { 1, { 2 } }, { 2, { 3, 1 } }, { 3, { 2 } } };
    graph k{ { 1, { 1 } } };
    graph l{ { 1000, { 2000000000 } }, { 2000000000, { 3000, 1000 } },
             { 3000, { 2000000000 } } };
    graph m{ { 1, { 1 } }, { 2, { 2 } } };

    assert( !hamilton( g ) );
    assert(  hamilton( h ) );
    assert( !hamilton( i ) );
    assert( !hamilton( j ) );
    assert(  hamilton( k ) );
    assert( !hamilton( l ) );
    assert( !hamilton( m ) );

    return 0;
}
