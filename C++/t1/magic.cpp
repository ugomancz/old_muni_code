#include <cassert>
#include <numeric>
#include "magic.hpp"

magic::magic(const int n) : square(n, std::vector<int>(n)),
                            magic_number(((n * n * (n * n + 1)) / 2) / n) {
    assert(n >= 1);
    for (int i = 1; i <= n * n; i++) {
        possible_values.emplace(i);
    }
}

int magic::get(const int x, const int y) const {
    assert(x >= 0 && static_cast<size_t>(x) < square.size());
    assert(y >= 0 && static_cast<size_t>(y) < square.size());
    return square[x][y];
}

void magic::set(const int x, const int y, const int v) {
    assert(x >= 0 && static_cast<size_t>(x) < square.size());
    assert(y >= 0 && static_cast<size_t>(y)< square.size());
    square[x][y] = v;
}

bool magic::solve() {
    if (solved()) {
        return true;
    }
    size_t row, col;
    for (row = 0; row < square.size(); ++row) {
        for (col = 0; col < square.size(); ++col) {
            if (empty_cell(row, col)) {
                for (const int &value : possible_values) {
                    if (!used(value)) {
                        set(static_cast<int>(row), static_cast<int>(col), value);
                        /* Following are optimizations in case we already filled an
                         * entire column/row but id doesn't sum up to the magic number */
                        if (row == square.size() - 1 && sum_column(col) != magic_number) {
                            continue;
                        }
                        if (col == square.size() - 1 && sum_row(row) != magic_number) {
                            continue;
                        }
                        if (solve()) {
                            return true;
                        }
                    }
                }
                set(static_cast<int>(row), static_cast<int>(col), 0);
                break;
            }
        }
    }
    return false;
}


bool magic::solved() {
    /* check if square is complete */
    for (const auto &vector: square) {
        for (const int number : vector) {
            if (number == 0) {
                return false;
            }
        }
    }
    /* check sums of diagonals */
    int rising_diagonal = 0, falling_diagonal = 0;
    for (size_t i = 0; i < square.size(); i++) {
        rising_diagonal += get(static_cast<int>(i), static_cast<int>(i));
        falling_diagonal += get(static_cast<int>(i), static_cast<int>(square.size() - i - 1));
    }
    if (rising_diagonal != magic_number || falling_diagonal != magic_number) {
        return false;
    }
    /* check sums of rows and columns */
    for (size_t i = 0; i < square.size(); i++) {
        if (sum_row(i) != magic_number || sum_column(i) != magic_number) {
            return false;
        }
    }
    return true;
}

bool magic::used(const size_t value) const {
    assert(value > 0 && value <= square.size() * square.size());
    for (const auto &vector: square) {
        for (const int number : vector) {
            if (static_cast<size_t>(number) == value) {
                return true;
            }
        }
    }
    return false;
}


int magic::sum_column(const size_t col) const {
    assert(col < square.size());
    int result = 0;
    for (const auto &row : square) {
        result += row.at(col);
    }
    return result;
}

int magic::sum_row(const size_t row) const {
    assert(row < square.size());
    return std::accumulate(square.at(row).begin(), square.at(row).end(), 0);
}

bool magic::empty_cell(size_t row, size_t col) const {
    return get(static_cast<int>(row),static_cast<int>(col)) == 0;
}

int main() {
    /* tests go here */
}
