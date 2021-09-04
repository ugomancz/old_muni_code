package cz.muni.fi.pb162.find.impl.comparators;

import cz.muni.fi.pb162.find.comparators.BasicComparator;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;

/**
 * compares files based on their extensions
 *
 * @author Ondrej Kostik
 */
public class FileExtensionComparator implements BasicComparator {
    private BasicComparator next;

    /**
     * constructor
     *
     * @param next is next comparator in case this one deems entries as equivalent
     */
    public FileExtensionComparator(BasicComparator next) {
        this.next = next;
    }

    @Override
    public BasicComparator getNextComparator() {
        return next;
    }

    @Override
    public int compare(SearchEntry o1, SearchEntry o2) {
        String firstExtension = getExtension(o1);
        String secondExtension = getExtension(o2);
        int result = 0;
        result = firstExtension.compareTo(secondExtension);
        if (result != 0 || next == null) {
            return result;
        }
        return getNextComparator().compare(o1, o2);
    }

    private String getExtension(SearchEntry entry) {
        String[] split = entry.getFileName().toString().split("\\.");
        if (split.length < 2) {
            return "";
        }
        return split[split.length - 1];
    }
}
