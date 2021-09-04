#include <iostream>
#include <cassert>
#include <numeric>
#include "magic.hpp"

/** zbytečně vytváříte dočasný objekt a ten pak kopírujete (vnější ‹std::vector›
 ** je zbytečný, inicializační sekce volá přímo konstruktor **/
magic::magic(const int n) : square(std::vector<std::vector<int>>(n, std::vector<int>(n))),
                            magic_number(((n * n * (n * n + 1)) / 2) / n), size(n) {
    assert(n >= 1);
    /** použito jen jednou – bylo by lepší si na to místo dát tento cyklus než
     ** si ukládat všechny možné hodnoty po celou dobu **/
    for (int i = 1; i <= n * n; i++) {
        possible_values.emplace(i);
    }
}

int magic::get(const int x, const int y) const {
    assert(x >= 0 && x < size);
    assert(y >= 0 && y < size);
    /** vzhledem k tomu, že už jste rozměry zkontroloval pomocí assertu by bylo
     ** rozumnější indexovat operátorem [] **/
    return square.at(x).at(y);
}

void magic::set(const int x, const int y, const int v) {
    assert(x >= 0 && x < size);
    assert(y >= 0 && y < size);
    /** opět **/
    square.at(x).at(y) = v;
}

bool magic::solve() {
    if (solved()) {
        return true;
    }
    int row = 0, col = 0;
    for (int i = 0; i < size * size; i++) {
        /** dva for cykly by byly podle mě jasnější… byť je to detail **/
        row = i / size;
        col = i % size;
        if (empty_cell(row, col)) {
            for (const int &value : possible_values) {
                if (unused(value)) {
                    set(row, col, value);
                    /** tohle řeší doplněnost jen v některých případech, může se
                     ** stát, že všechny další pozice už jsou předvyplněné (což
                     ** teda nevadí, je to heuristika na urychlení, takže to
                     ** berte jen jako upozornění **/
                    /* Following are optimizations in case we already filled an
                     * entire column/row but id doesn't sum up to the magic number */
                    if (row == size - 1 && sum_column(col) != magic_number) {
                        continue;
                    }
                    if (col == size - 1 && sum_row(row) != magic_number) {
                        continue;
                    }
                    if (solve()) {
                        return true;
                    }
                }
            }
            break;
        }
    }
    /** dávalo by mi větší smysl dát to hned za cyklus přes možné hodnoty, musel
     ** jsem se chvíli zamyslet než mi došlo, že je to tu dobře **/
    set(row, col, 0);
    return false;
}


bool magic::solved() {
    /* check if square is complete */
    /** tip: const auto & **/
    for (const std::vector<int> &vector: square) {
        /** zbytečná reference, int je malý, dává větší smysl ho prostě
         ** zkopírovat **/
        for (const int &number : vector) {
            if (number == 0) {
                return false;
            }
        }
    }
    /* check sums of diagonals */
    int diagonal_sum = 0;
    for (int i = 0; i < size; i++) {
        diagonal_sum += get(i, i);
    }
    if (diagonal_sum != magic_number) {
        return false;
    }
    /** duplikace kódu **/
    diagonal_sum = 0;
    for (int i = 0; i < size; i++) {
        diagonal_sum += get(i, size - i - 1);
    }
    if (diagonal_sum != magic_number) {
        return false;
    }
    /* check sums of rows and columns */
    for (int i = 0; i < size; i++) {
        if (sum_row(i) != magic_number || sum_column(i) != magic_number) {
            return false;
        }
    }
    return true;
}

bool magic::unused(const int value) const {
    assert(value > 0 && value <= size * size);
    for (const std::vector<int> &vector: square) {
        for (const int &number : vector) {
            if (number == value) {
                return false;
            }
        }
    }
    return true;
}


int magic::sum_column(const int col) {
    assert(col >= 0 && col < size);
    int result = 0;
    for (const auto &row : square) {
        result += row.at(col);
    }
    return result;
}

/** ve skutečnosti lze všechny sumy vyřešit jedou funkcí **/
int magic::sum_row(const int row) {
    assert(row >= 0 && row < size);
    return std::accumulate(square.at(row).begin(), square.at(row).end(), 0);
}

bool magic::empty_cell(int row, int col) const {
    return get(row, col) == 0;
}

int main() {
    magic m(2);
    std::cout << std::boolalpha << !m.solve();
}
