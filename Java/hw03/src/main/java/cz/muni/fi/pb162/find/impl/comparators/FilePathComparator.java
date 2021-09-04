package cz.muni.fi.pb162.find.impl.comparators;

import cz.muni.fi.pb162.find.comparators.BasicComparator;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;

/**
 * compares files based on their path
 *
 * @author Ondrej Kostik
 */
public class FilePathComparator implements BasicComparator {
    @Override
    public BasicComparator getNextComparator() {
        return null;
    }

    @Override
    public int compare(SearchEntry o1, SearchEntry o2) {
        return o1.getPath().toString().compareTo(o2.getPath().toString());
    }
}
