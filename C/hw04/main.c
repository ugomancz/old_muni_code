/**
 * @file    main.c
 * \mainpage HW04 Documentation
 *
 *
 * On the 'Files' page, there is a list of documented files with brief descriptions.
 *
*/

#include "graph.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Reads one line from input file and checks for proper
 * number of "columns"
 *
 * @return string containing the line or NULL on failure
 */
char *readLine(FILE *in) {
    int length = 0;
    char *line = NULL;
    int letter = 0;
    int index = 0;
    while ((letter = fgetc(in)) != '\n' && letter != EOF) {
        if (index >= length - 1) { // allocating more memory
            length += 100;
            char *newLine = realloc(line, (size_t) length);
            if (!newLine) { // allocation failed
                fprintf(stderr, "Couldn't allocate memory\n");
                free(line);
                return NULL;
            }
            line = newLine;
        }
        line[index] = (char) letter;
        ++index;
    }
    if (letter == EOF) { // no more lines
        free(line);
        return NULL;
    }
    int delimiterCount = 0;
    for (int i = 0; i < index; i++) { // counting "columns"
        if (line[i] == ',') {
            ++delimiterCount;
        }
    }
    if (delimiterCount != 6) { // wrong number of columns
        fprintf(stderr, "Input in wrong format\n");
        free(line);
        return NULL;
    }
    line[index] = '\0';
    return line;
}

/**
 * \brief Reads nodes from input and adds them to graph
 * @param graph
 * @param in
 * @return 0 on success, -1 on failure
 */
int readNodes(Graph *graph, FILE *in) {
    char *line = NULL;
    while ((line = readLine(in))) { // while there are lines on input
        unsigned int id = (unsigned int) strtol(line, NULL, 0);
        if (!graph_insert_node(graph, id)) { // if insertion to graph fails
            fprintf(stderr, "Program ran out of memory\n");
            free(line);
            return -1;
        }
        free(line);
    }
    return 0;
}

/**
 * Helper function, because implementation of strtok didn't work on char*
 *
 * @param line line to be tokenized
 * @param delim
 * @param counter how many delimiters are to be passed before a pointer is returned
 * @return pointer to first char after counter'th delimiter
 */
char *myStrTok(char *line, char delimiter, int counter) {
    int index = 0;
    while (counter > 0) {
        if (line[index] == delimiter) {
            --counter;
        }
        ++index;
    }
    return line + index;
}

/**
 * \brief Reads edges from input and adds them to graph
 * @param graph
 * @param in
 * @return 0 on success, -1 on failure
 */
int readEdges(Graph *graph, FILE *in) {
    char *line = NULL;
    while ((line = readLine(in))) { // while there are lines on input
        unsigned int from = strtol(line, NULL, 0);
        unsigned int to = strtol(myStrTok(line, ',', 1), NULL, 0);
        unsigned int delay = strtol(myStrTok(line, ',', 3), NULL, 0);
        if (!graph_insert_edge(graph, from, to, delay)) { // if insertion to graph fails
            fprintf(stderr, "Program ran out of memory\n");
            free(line);
            return -1;
        }
        free(line);
    }
    return 0;
}

/**
 * Implementation of Dijkstra algorithm over Graph, uses minimal
 * heap Heap as a priority queue.
 *
 * @param graph Graph to run the algorithm on
 * @param start ID of the beginning node
 */
void dijkstra(Graph *graph, unsigned int start) {
    Heap *queue = heap_new_from_graph(graph);
    if (heap_is_empty(queue)) { // heap is empty
        return;
    }
    heap_decrease_distance(queue, graph_get_node(graph, start), 0, NULL); // sets starting Node's distance to 0
    while (!heap_is_empty(queue)) {
        Node *closest = heap_extract_min(queue); // selects the closest Node from queue
        struct edge *edges = node_get_edges(closest);
        for (unsigned short i = 0; i < node_get_n_outgoing(closest); i++) { // for all edges coming out of closest node
            unsigned int distance = node_get_distance(closest) + edges[i].mindelay;
            if (node_get_distance(edges[i].destination) > distance) { // newly found path is shorter than the old one
                heap_decrease_distance(queue, edges[i].destination, distance, closest);
            }
        }
    }
    heap_free(queue);
}

/**
 * Helper function to find value of edge between two nodes
 *
 * @param prev the "from" node
 * @param next the "to" node
 * @return value of edge on success or -1 on failure
 */
int getEdgeValue(Node *prev, Node *next) {
    for (unsigned short i = 0; i < node_get_n_outgoing(prev); i++) {
        struct edge *edges = node_get_edges(prev);
        if (edges[i].destination == next) {
            return edges[i].mindelay;
        }
    }
    fprintf(stderr, "No edges leading to the node from its previous one\n");
    return -1;
}

/**
 * Writes a GraphWiz representation of the shortest path found
 * to selected stream
 *
 * @param node the final node
 * @param out stream to be written to
 */
int output(Node *end, Node *start, FILE *out) {
    Node *prev = node_get_previous(end);
    if (!prev) { // no previous to last node
        fprintf(stderr, "No path found\n");
        return -1;
    }
    fprintf(out, "digraph {\n");
    while (prev) {
        fprintf(out, "\t%u -> %u [label=%u];\n", node_get_id(prev), node_get_id(end), getEdgeValue(prev, end));
        end = prev;
        prev = node_get_previous(prev);
    }
    if (end != start) { // backtracking from last node didn't reach starting node
        fprintf(stderr, "No path found\n");
        return -1;
    }
    fprintf(out, "}");
    return 0;
}

/**
 * Helper function to close two streams at once
 */
void closeBoth(FILE *nodes, FILE *edges) {
    fclose(nodes);
    fclose(edges);
}

/**
 * Program's main purpose is to find shortest path between given nodes
 * in graph made out of loaded data and write back (possibly to a file)
 * it's graph representation in GraphWiz compatible format
 *
 * PS: Personally, I think this main could've been shorter and prettier,
 * but let's be honest, this is probably the last hw I'll do anyway
 *
 * @param argc takes 4 or 5 arguments
 * @param argv nodes input, edges input, beginning node, final node [output file]
 * @return 0 on success, -1 on failure
 */
int main(int argc, char* argv[]) {
    if (argc != 5 && argc != 6) { // checks number of arguments
        fprintf(stderr, "Wrong number of arguments, please use ./dimes [nodes file] "
                        "[edges file] [start node] [finishing node] and optional [output file]\n");
        return -1;
    }
    Graph *graph = graph_new();
    if (!graph) {
        fprintf(stderr, "Couldn't create a graph due to memory issues\n");
        return -1;
    }
    FILE *nodes = fopen(argv[1], "r");
    if (!nodes) {
        fprintf(stderr, "Couldn't open nodes file\n");
        graph_free(graph);
        return -1;
    }
    FILE *edges = fopen(argv[2], "r");
    if (!edges) {
        fprintf(stderr, "Couldn't open edges file\n");
        fclose(nodes);
        graph_free(graph);
        return -1;
    }
    if (readNodes(graph, nodes)) {
        fprintf(stderr, "Couldn't read nodes file\n");
        graph_free(graph);
        closeBoth(nodes, edges);
        return -1;
    }
    if (readEdges(graph, edges)) {
        fprintf(stderr, "Couldn't read edges file\n");
        graph_free(graph);
        closeBoth(nodes, edges);
        return -1;
    }
    unsigned int start = strtol(argv[3], NULL, 0);
    unsigned int finish = strtol(argv[4], NULL, 0);
    if (graph_get_node(graph, start) == NULL || graph_get_node(graph, finish) == NULL) {
        fprintf(stderr, "Requested nodes are not in the graph\n");
        graph_free(graph);
        closeBoth(nodes, edges);
        return -1;
    }
    dijkstra(graph, start);
    if (argc == 6) {
        FILE *out = fopen(argv[5], "w");
        if (!out) {
            fprintf(stderr, "Couldn't create or write to output.txt\n");
            closeBoth(nodes, edges);
            graph_free(graph);
            return -1;
        }
        if (output(graph_get_node(graph, finish), graph_get_node(graph, start), out)) {
            graph_free(graph);
            closeBoth(nodes, edges);
            fclose(out);
            return -1;
        }
        closeBoth(nodes, edges);
        fclose(out);
        graph_free(graph);
        return 0;
    }
    if (output(graph_get_node(graph, finish), graph_get_node(graph, start), stdout)) {
        closeBoth(nodes, edges);
        graph_free(graph);
        return -1;
    }
    closeBoth(nodes, edges);
    graph_free(graph);
    return 0;
}