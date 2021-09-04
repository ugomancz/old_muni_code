package cz.muni.fi.pb162.find.impl.comparators;

import cz.muni.fi.pb162.find.comparators.BasicComparator;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;

/**
 * compares files based on their names
 *
 * @author Ondrej Kostik
 */
public class FileNameComparator implements BasicComparator {
    private BasicComparator next;

    /**
     * constructor
     *
     * @param next is next comparator in case this one deems entries as equivalent
     */
    public FileNameComparator(BasicComparator next) {
        this.next = next;
    }

    @Override
    public BasicComparator getNextComparator() {
        return next;
    }

    @Override
    public int compare(SearchEntry o1, SearchEntry o2) {
        int result = o1.getFileName().toString().compareTo(o2.getFileName().toString());
        if (result != 0 || next == null) {
            return result;
        }
        return getNextComparator().compare(o1, o2);
    }
}
