/** OK, @A **/
#ifndef CELLULAR_H
#define CELLULAR_H


/* The goal of this task is to implement a simple simulator for
 * one-dimensional cellular automata. You will implement this
 * simulator as a class, the interface of which is described below
 * You are free to add additional methods and data members to the
 * class, and additional classes and functions to the file, as you
 * see fit. You must, however, keep the entire interface in this
 * single file. The implementation can be in either ‹cellular.hpp›
 * or in ‹cellular.cpp›. Only these two files will be submitted. */

#include <vector>

/* The class ‹automaton_state› represents the state of a 1D, binary
 * cellular automaton, defined on a «cells» with a given number of
 * cells, which are numbered clockwise, starting from 0. The number
 * of cells can be adjusted at runtime, using the methods ‹extend›
 * and ‹reduce›. The indices are always kept contiguous, and values
 * of cells at existing (remaining) indices remain unchanged. */

class automaton_state {
private:
    std::vector<bool> cells;

public:

    /* Construct a state with ‹n› cells, all set to 0. */
    explicit automaton_state(int n);

    /* Read and write values of individual cells, and get the
     * current size. */

    bool get(int index) const;

    void set(int index, bool value);

    int size() const;

    /* Resize the cells by adding or removing ‹m› cells. Newly
     * added cells are always initialized to 0. */

    void extend(int m);

    void reduce(int m);
};

/* The ‹automaton› class represents the automaton itself. The
 * automaton keeps its state internally and allows the user to
 * perform simulation on this internal state. Initially, the state
 * of the automaton is 0 (false) everywhere. The rule is given to
 * the constructor by its Wolfram code. The left-to-right reading of
 * the rule refers to cells on the cells in a clockwise order. */

class automaton {
private:
    bool rules[8];
    automaton_state inner_state;

    void parse_rules(int rule);

public:

    /* Constructs an automaton based on a rule given by its Wolfram
     * code, and with ‹n› cells, all set to 0. */

    automaton(int rule, int n);

    automaton(int rule, automaton_state state);

    /* Read from and write into cells of the current state. */

    bool get(int index) const;

    void set(int index, bool value);

    /* Obtain a copy of the entire state at once (‹state›) or reset
     * the automaton to a new state in one call (‹reset›). */

    automaton_state state() const;

    void reset(const automaton_state &s);

    /* Run the automaton – either perform a single step (update each
     * cell exactly once) or a given number of steps (assume a
     * non-negative number of steps). */

    void step();

    void run(int steps);
};

/* The ‹compute_cell› function takes a rule number, an initial state
 * ‹start›, the number of steps and an index into the state; it then
 * returns the state of the indexed cell after ‹steps› rounds of
 * computation. Again, the number of steps is non-negative. */

bool compute_cell(int rule, const automaton_state &start,
                  int steps, int index);

#endif // CELLULAR_H
