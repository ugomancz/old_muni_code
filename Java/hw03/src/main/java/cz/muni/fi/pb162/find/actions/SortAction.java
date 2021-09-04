package cz.muni.fi.pb162.find.actions;

import java.util.List;

import cz.muni.fi.pb162.find.filesystem.SearchEntry;

/**
 * Sorts all the search entities
 *
 * @author pstanko
 */
public interface SortAction {
    /**
     * Sorts all the search entities returned from filter.
     * The order of elements should be determined by {@link cz.muni.fi.pb162.find.ApplicationOptions#getSort()}
     *
     * {@link cz.muni.fi.pb162.find.tools.SortFactory#create(String)} can be used to create the comparator chain.
     *
     * @param entries - Unsorted entries
     * @return Sorted entries
     */
    List<SearchEntry> sorted(List<SearchEntry> entries);
}
