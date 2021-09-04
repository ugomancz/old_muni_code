#include <cassert>
#include "cellular.hpp"

int euc_modulo(const int a, const int b) {
    return a < 0 ? (((a % b) + b) % b) : (a % b);
}

automaton_state::automaton_state(const int n) : cells(std::vector<bool>(n)) {
    assert(n >= 0);
}

bool automaton_state::get(const int index) const {
    assert(index >= 0 && index < size());
    return cells.at(index);
}

void automaton_state::set(const int index, const bool value) {
    assert(index >= 0 && index < size());
    cells.at(index) = value;
}

int automaton_state::size() const {
    return static_cast<int>(cells.size());
}

void automaton_state::extend(const int m) {
    assert(m >= 0);
    cells.resize(cells.size() + m, false);
}

void automaton_state::reduce(const int m) {
    assert(m >= 0);
    cells.resize(cells.size() - m);
}

automaton::automaton(const int rule, const int n) : automaton(rule, automaton_state(n)) {
    assert(n >= 0);
}

automaton::automaton(const int rule, automaton_state state) : inner_state(std::move(state)) {
    assert(rule >= 0 && rule <= 255);
    parse_rules(rule);
}

bool automaton::get(const int index) const {
    assert(index >= 0 && index < inner_state.size());
    return inner_state.get(index);
}

void automaton::set(const int index, const bool value) {
    assert(index >= 0 && index < inner_state.size());
    inner_state.set(index, value);
}

automaton_state automaton::state() const {
    return inner_state;
}

void automaton::reset(const automaton_state &s) {
    inner_state = s;
}

/*
 * The result of a step on each cell is first saved in the temporary
 * new_cells and after all the steps are performed, new_cells replaces
 * existing cells.
 */
void automaton::step() {
    automaton_state new_state(inner_state.size());
    for (int i = 0; i < inner_state.size(); i++) {
        int cells_value = get(euc_modulo(i - 1, inner_state.size())) << 2
                          | get(i) << 1
                          | get((euc_modulo(i + 1, inner_state.size())));
        new_state.set(i, rules[cells_value]);
    }
    inner_state = std::move(new_state);
}

void automaton::run(const int steps) {
    assert(steps >= 0);
    for (int i = 0; i < steps; ++i) {
        step();
    }
}

/*
 * Parses given rule number to pairs of (cells value, new value),
 * cells value being the rule applied based on a cell and it's
 * immediate surroundings and new value being the value which
 * the cell is to be set to.
 */
void automaton::parse_rules(const int rule) {
    for (int i = 0; i < 8; i++) {
        rules[i] = (rule >> i) % 2;
    }
}

bool compute_cell(int rule, const automaton_state &start, int steps, int index) {
    assert(rule >= 0 && rule <= 255);
    assert(steps >= 0);
    assert(index >= 0 && index < start.size());
    automaton automaton(rule, start);
    automaton.run(steps);
    return automaton.get(index);
}

int main() {
    /* tests go here */
}
