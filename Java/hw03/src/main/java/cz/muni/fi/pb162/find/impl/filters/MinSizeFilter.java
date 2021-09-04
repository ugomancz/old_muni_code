package cz.muni.fi.pb162.find.impl.filters;

import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import cz.muni.fi.pb162.find.filters.BasicFilter;

import java.util.List;

/**
 * filter based on minimum size of file/directory
 *
 * @author Ondrej Kostik
 */
public class MinSizeFilter extends BasicFilter {
    private long threshold;

    /**
     * constructor
     *
     * @param paths     list of entries to filter
     * @param threshold the minimum size of files to filter out
     */
    public MinSizeFilter(List<SearchEntry> paths, long threshold) {
        super(paths);
        this.threshold = threshold;

    }

    @Override
    public boolean filter(SearchEntry path) {
        return (path.getSize() >= threshold);
    }

}
