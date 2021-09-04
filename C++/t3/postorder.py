from random import randint, choice


def addEdge(adj, v, w):
    adj[v].add(w)

    # Note: the graph is undirected
    adj[w].add(v)
    return adj


# Assigns colors (starting from 0) to all
# vertices and prints the assignment of colors
def greedyColoring(adj, V):
    result = [-1] * V

    # Assign the first color to first vertex
    result[0] = 0;

    # A temporary array to store the available colors.
    # True value of available[cr] would mean that the
    # color cr is assigned to one of its adjacent vertices
    available = [False] * V

    # Assign colors to remaining V-1 vertices
    for u in range(1, V):

        # Process all adjacent vertices and
        # flag their colors as unavailable
        for i in adj[u]:
            if (result[i] != -1):
                available[result[i]] = True

        # Find the first available color
        cr = 0
        while cr < V:
            if (available[cr] == False):
                break

            cr += 1

        # Assign the found color
        result[u] = cr

        # Reset the values back to false
        # for the next iteration
        for i in adj[u]:
            if (result[i] != -1):
                available[result[i]] = False
    return max(result) + 1
#####################################################################
class Graph:
    vertices = []
    edges = set()

    def generate_vertices(self, n):
        for i in range(n):
            self.vertices.append(i)

    def generate_edges(self, n):
        for i in range(n):
            one, two = choice(self.vertices), choice(self.vertices)
            self.edges.add((one, two))
            self.edges.add((two, one))
    def print(self):
        result = ""
        result  += "graph g{}".format(randint(0,50000))
        result += " {"
        for edge in self.edges:
            result += "{"
            result += "{},{}".format(edge[0], edge[1])
            result += "},"
        result = result[:-1]
        result += "};"
        print(result)
    @property
    def chromatic_number(self):
        g1 = [set() for _ in range(len(self.vertices))]
        for edge in self.edges:
            g1 = addEdge(g1,edge[0],edge[1])
        print(g1)
        return greedyColoring(g1, len(self.vertices))


def main():
    for _ in range(1):
        g = Graph()
        g.generate_vertices(10)
        g.generate_edges(10)
        g.print()
        print(f"chromatic: {g.chromatic_number}")


if __name__ == "__main__":
    main()
