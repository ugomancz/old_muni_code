package cz.muni.fi.pb162.find.impl.actions;

import cz.muni.fi.pb162.find.ApplicationOptions;
import cz.muni.fi.pb162.find.actions.SortAction;
import cz.muni.fi.pb162.find.comparators.BasicComparator;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import cz.muni.fi.pb162.find.impl.comparators.FileExtensionComparator;
import cz.muni.fi.pb162.find.impl.comparators.FileNameComparator;
import cz.muni.fi.pb162.find.impl.comparators.FilePathComparator;
import cz.muni.fi.pb162.find.impl.comparators.FileSizeComparator;

import java.util.Collections;
import java.util.List;

/**
 * main execution point for ordering the filtered results
 *
 * @author Ondrej Kostik
 */
public class SortActionImpl implements SortAction {
    private ApplicationOptions opts;

    /**
     * constructor
     *
     * @param opts is an ApplicationOptions instance
     */
    public SortActionImpl(ApplicationOptions opts) {
        this.opts = opts;
    }

    @Override
    public List<SearchEntry> sorted(List<SearchEntry> entries) {
        entries.sort(getComparator(new StringBuilder(opts.getSort())));
        return Collections.unmodifiableList(entries);

    }

    private BasicComparator getComparator(StringBuilder sort) {
        char firstChar = sort.charAt(0);
        switch (firstChar) {
            case 's':
                if (sort.length() == 1) {
                    return new FileSizeComparator(null);
                }
                return new FileSizeComparator(getComparator(sort.deleteCharAt(0)));
            case 'e':
                if (sort.length() == 1) {
                    return new FileExtensionComparator(null);
                }
                return new FileExtensionComparator(getComparator(sort.deleteCharAt(0)));
            case 'n':
                if (sort.length() == 1) {
                    return new FileNameComparator(null);
                }
                return new FileNameComparator(getComparator(sort.deleteCharAt(0)));
            default:
                return new FilePathComparator();
        }
    }
}
