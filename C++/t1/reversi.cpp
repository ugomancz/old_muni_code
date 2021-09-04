#include <cassert>
#include <iostream>
#include <numeric>
#include "reversi.hpp"

reversi::reversi(int size) : board_size(size),
                             board(std::vector(size, std::vector(size, std::vector(size, NONE)))) {
    assert(size % 2 == 0);
    assert(size >= 2);
    /* placing initial stones */
    place_stone(1, 1, 1, WHITE, true);
    place_stone(1, -1, -1, WHITE, true);
    place_stone(-1, -1, 1, WHITE, true);
    place_stone(-1, 1, -1, WHITE, true);
    place_stone(-1, -1, -1, BLACK, true);
    place_stone(-1, 1, 1, BLACK, true);
    place_stone(1, 1, -1, BLACK, true);
    place_stone(1, -1, 1, BLACK, true);
}

bool reversi::play(int x, int y, int z) {
    if (x == 0 and y == 0 and z == 0 and not has_available_moves(current_stone)) { // special case
        next_player();
        return true;
    }
    int internal_x = board_size / 2 + (x > 0 ? --x : x);
    int internal_y = board_size / 2 + (y > 0 ? --y : y);
    int internal_z = board_size / 2 + (z > 0 ? --z : z);
    if (do_legal_move(internal_x, internal_y, internal_z, current_stone)) {
        next_player();
        return true;
    } else {
        return false;
    }
}

bool reversi::finished() const {
    return not(has_available_moves(WHITE) or has_available_moves(BLACK));
}

int reversi::result() const {
    short result = 0;
    for (const auto &x : board) {
        for (const auto &y: x) {
            for (const auto &stone : y) {
                if (stone == BLACK) {
                    result--;
                } else {
                    result++;
                }
            }
        }
    }
    return result;
}

void reversi::next_player() {
    current_stone = (current_stone == BLACK ? WHITE : BLACK);
}

void reversi::place_stone(int x, int y, int z, const stone stone, const bool adjust_coordinates) {
    if (adjust_coordinates) { // initial placement
        int internal_x = board_size / 2 + (x > 0 ? --x : x);
        int internal_y = board_size / 2 + (y > 0 ? --y : y);
        int internal_z = board_size / 2 + (z > 0 ? --z : z);
        board.at(internal_x).at(internal_y).at(internal_z) = stone;
    } else {
        board.at(x).at(y).at(z) = stone;
    }
}

stone reversi::get_stone(const int x, const int y, const int z) const {
    return board.at(x).at(y).at(z);
}

bool reversi::has_available_moves(const stone stone) const {
    for (int x = 0; x < board_size; x++) {
        for (int y = 0; y < board_size; y++) {
            for (int z = 0; z < board_size; z++) {
                if (get_stone(x, y, z) == NONE and is_legal_move(x, y, z, stone)) {
                    return true;
                }
            }
        }
    }
    return false;
}

/* Both following methods use vector of size 26 because the cell at [x,y,z] can
 * be surrounded by up to 26 other cells in different directions so the vector
 * has 26 members, each keeps track of whether the corresponding direction holds
 * a valid row of stones and if so, how far is the end of this row.
 */
bool reversi::is_legal_move(const int x, const int y, const int z, const stone stone) const {
    auto indices = std::vector<std::pair<bool, int>>(26, {false, 0});
    map_surrounding_stones(x, y, z, stone, indices);

    return std::accumulate(indices.begin(), indices.end(), false,
                           [](bool result, auto pair) { return result || pair.first; });
}

bool reversi::do_legal_move(const int x, const int y, const int z, const stone stone) {
    if (get_stone(x, y, z) != NONE) { // a stone has already been placed here
        return false;
    }
    auto indices = std::vector<std::pair<bool, int>>(26, {false, 0});
    map_surrounding_stones(x, y, z, stone, indices);
    if (!std::accumulate(indices.begin(), indices.end(), false,
                         [](bool result, auto pair) { return result || pair.first; })) {
        return false;
    }
    replace_surrounding_stones(x, y, z, stone, indices);
    return true;
}

void reversi::map_surrounding_stones(const int x, const int y, const int z, const stone stone,
                                     std::vector<std::pair<bool, int>> &indices) const {
    int new_x = x, new_y = y, new_z = z, direction = 0;
    for (const int x_multiplier : {-1, 0, 1}) {
        for (const int y_multiplier : {-1, 0, 1}) {
            for (const int z_multiplier : {-1, 0, 1}) {
                if (x_multiplier != 0 || y_multiplier != 0 || z_multiplier != 0) {
                    while ((new_x >= 0 && new_x < board_size) && (new_y >= 0 && new_y < board_size) &&
                           (new_z >= 0 && new_z < board_size)) {
                        if (indices.at(direction).second > 1 && get_stone(new_x, new_y, new_z) == stone) {
                            indices.at(direction).first = true;
                            break;
                        } else if (indices.at(direction).second > 0 && (get_stone(new_x, new_y, new_z) == NONE ||
                                                                        get_stone(new_x, new_y, new_z) == stone)) {
                            break;
                        }
                        indices.at(direction).second++;
                        new_x = x + x_multiplier * indices.at(direction).second;
                        new_y = y + y_multiplier * indices.at(direction).second;
                        new_z = z + z_multiplier * indices.at(direction).second;
                    }
                    direction++;
                    new_x = x, new_y = y, new_z = z;
                }
            }
        }
    }
}

void reversi::replace_surrounding_stones(const int x, const int y, const int z, const stone stone,
                                         std::vector<std::pair<bool, int>> &indices) {
    int new_x, new_y, new_z, direction = 0;
    for (const int x_multiplier : {-1, 0, 1}) {
        for (const int y_multiplier : {-1, 0, 1}) {
            for (const int z_multiplier : {-1, 0, 1}) {
                if (x_multiplier == 0 && y_multiplier == 0 && z_multiplier == 0) {
                    continue;
                }
                if (indices.at(direction).first) {
                    do {
                        new_x = x + x_multiplier * indices.at(direction).second;
                        new_y = y + y_multiplier * indices.at(direction).second;
                        new_z = z + z_multiplier * indices.at(direction).second;
                        place_stone(new_x, new_y, new_z, stone, false);
                        indices.at(direction).second--;
                    } while (new_x != x || new_y != y || new_z != z);
                }
                direction++;
            }
        }
    }
}

int main() {
    /* tests go here */
}
