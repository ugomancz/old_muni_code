/* In this exercise, we will do some basic statistics: median,
 * quartiles and mode. */

#include <utility>
#include <vector>
#include <forward_list>
#include <set>
#include <cassert>
#include <map>
#include <algorithm>

/* Implement the functions ‹mode›, ‹median› and ‹quartiles›, in such
 * a way that it accepts any sequential ‹std› container, with
 * element type that allows less-than and equality comparison.
 * Additional notes:
 *
 *  • ‹mode› returns an ‹std::set› of numbers, since there might be
 *    arbitrarily many: include any input number for which the number
 *    of occurrences is maximal
 *  • ‹median› return a single number; pick the smaller of the two
 *    elements if the median lies in between two different numbers
 *  • ‹quartiles› returns numbers at indices (size / 4) and ( ( 3 *
 *    size ) / 4 ) of the sorted input sequence, in an ‹std::pair›
 *    [this is slightly incorrect but simpler]. */

// mode:      ref. 15 lines
template<typename container_t>
auto mode(const container_t &container) {
    using value_t = typename container_t::value_type;
    if (container.empty()) {
        return std::set<value_t>();
    }
    std::map<value_t, size_t> occurrences;
    auto max_occurrence = [&occurrences]() { // returns (key,value) pair with highest value
        return *std::max_element(occurrences.begin(), occurrences.end(), [](const auto &v1, const auto &v2) {
            return v1.second < v2.second;
        });
    };
    for (const auto &member : container) { // count occurrences of values
        occurrences[member]++;
    }
    std::pair<value_t, size_t> max_value = max_occurrence();
    std::set<value_t> result{max_value.first};
    occurrences.erase(max_value.first);
    while (!occurrences.empty() && max_value.second == (max_value = max_occurrence()).second) {
        result.emplace(max_value.first);
        occurrences.erase(max_value.first);
    }
    return result;
}

// median:    ref.  7 lines
template<typename container_t>
auto median(container_t container) {
    using value_t = typename container_t::value_type;
    size_t size = std::distance(container.begin(), container.end());
    std::vector<value_t> sorted(size);
    std::partial_sort_copy(container.begin(), container.end(), sorted.begin(), sorted.end(),
                           [&](const auto v1, const auto v2) {
                               return v1 < v2;
                           });
    if (size % 2 == 1) {
        return sorted.at(size / 2);
    }
    return sorted.at(size / 2 - 1);
}

// quartiles: ref.  8 lines
template<typename container_t>
auto quartiles(const container_t &container) {
    using value_t = typename container_t::value_type;
    size_t size = std::distance(container.begin(), container.end());
    std::vector<value_t> sorted(size);
    std::partial_sort_copy(container.begin(), container.end(), sorted.begin(), sorted.end(),
                           [&](const auto v1, const auto v2) {
                               return v1 < v2;
                           });
    return std::pair<value_t, value_t>(sorted.at(size / 4), sorted.at(3 * size / 4));
}

int main()
{
    std::forward_list< int > fl;
    fl.push_front( 1 );
    fl.push_front( 3 );
    fl.push_front( 5 );
    fl.push_front( 3 );

    assert( median( fl ) == 3 );
    assert( mode( fl ) == std::set{ 3 } );
    assert( quartiles( fl ) == std::pair( 3, 5 ) );

    std::set< std::pair< int, int > > s;
    s.emplace( 1, 0 );
    s.emplace( 2, 0 );
    s.emplace( 2, 1 );
    s.emplace( 3, 1 );
    s.emplace( 4, 0 );
    assert( mode( s ) == s );
    assert( median( s ) == std::pair( 2, 1 ) );
    assert( quartiles( s ) == std::pair( std::pair( 2, 0 ),
                                         std::pair( 3, 1 ) ) );

    std::vector< double > v;
    v.push_back( 3.14 );
    v.push_back( 3.14 );
    v.push_back( 2.0 );
    v.push_back( 2.0 );
    v.push_back( 2.71 );

    assert( mode( v ) == ( std::set{ 2.0, 3.14 } ) );
    assert( median( v ) == 2.71 );
    assert( quartiles( v ) == std::pair( 2.0, 3.14 ) );
}
