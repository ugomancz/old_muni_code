package cz.muni.fi.pb162.find.impl.comparators;

import cz.muni.fi.pb162.find.comparators.BasicComparator;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;

/**
 * compares files based on their size
 *
 * @author Ondrej Kostik
 */
public class FileSizeComparator implements BasicComparator {
    private BasicComparator next;

    /**
     * constructor
     *
     * @param next is next comparator in case this one deems entries as equivalent
     */
    public FileSizeComparator(BasicComparator next) {
        this.next = next;
    }

    @Override
    public BasicComparator getNextComparator() {
        return next;
    }

    @Override
    public int compare(SearchEntry o1, SearchEntry o2) {
        int result = Long.compare(o1.getSize(), o2.getSize());
        if (result != 0 || next == null) {
            return result;
        }
        return getNextComparator().compare(o1, o2);
    }
}
