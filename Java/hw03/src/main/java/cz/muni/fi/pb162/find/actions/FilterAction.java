package cz.muni.fi.pb162.find.actions;

import java.util.List;

import cz.muni.fi.pb162.find.filesystem.SearchEntry;

/**
 * This interface will be used for filtering the search entities
 * Implementation will take all the search entities and applies all the filters,
 * that has been specified by passed options.
 *
 * @author pstanko
 */
public interface FilterAction {
    /**
     * Takes search entities that has been returned from {@link cz.muni.fi.pb162.find.filesystem.FSWalkResult}
     * Applies all the filters that have been enabled and returns filtered entries.
     *
     * To check which filters are active use {@link cz.muni.fi.pb162.find.ApplicationOptions}
     *
     * @param entries - Not filtered search entities
     * @return filtered search entities
     */
    List<SearchEntry> filter(List<SearchEntry> entries);
}
