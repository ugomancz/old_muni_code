package cz.muni.fi.pb162.find.impl.filters;

import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import cz.muni.fi.pb162.find.filters.BasicFilter;

import java.util.List;

/**
 * filter based on file/directory name.
 *
 * @author Ondrej Kostik
 */
public class FileNameFilter extends BasicFilter {
    private String regex;

    /**
     * constructor
     *
     * @param paths list of entries to filter
     * @param regex the regex to be found in file name
     */
    public FileNameFilter(List<SearchEntry> paths, String regex) {
        super(paths);
        this.regex = regex;
    }

    @Override
    public boolean filter(SearchEntry path) {
        return (path.getFileName().toString().matches(regex));
    }
}
