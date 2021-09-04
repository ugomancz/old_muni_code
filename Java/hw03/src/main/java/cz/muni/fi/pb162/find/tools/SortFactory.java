package cz.muni.fi.pb162.find.tools;

import cz.muni.fi.pb162.find.comparators.BasicComparator;
import cz.muni.fi.pb162.find.impl.comparators.FileExtensionComparator;
import cz.muni.fi.pb162.find.impl.comparators.FileNameComparator;
import cz.muni.fi.pb162.find.impl.comparators.FilePathComparator;
import cz.muni.fi.pb162.find.impl.comparators.FileSizeComparator;

/**
 * Factory class that creates instances of comparators
 * Only public method is create, creates instance of comparators
 *
 * @author pstanko
 */
public class SortFactory {

    /**
     * Can be static because file path comparator does not keep any state, nothing to change.
     */
    private static final FilePathComparator DEFAULT_COMPARATOR = new FilePathComparator();

    /**
     * Static method that returns a decorated basic comparator
     * Comparators are in specific order (param)
     *
     * see {@link cz.muni.fi.pb162.find.ApplicationOptions#getSort()}
     *
     * @param order string representing the order of comparators
     * @return comparator chain for given string
     */
    public static BasicComparator create(String order) {
        BasicComparator result = DEFAULT_COMPARATOR;

        for (int i = order.length() - 1; i >= 0; i--) {
            char c = order.charAt(i);
            result = yield(c, result);
        }

        return result;
    }

    private static BasicComparator yield(char ch, BasicComparator nextComparator) {
        switch (ch) {
            case 'f':
                return DEFAULT_COMPARATOR;
            case 's':
                return new FileSizeComparator(nextComparator);
            case 'e':
                return new FileExtensionComparator(nextComparator);
            case 'n':
                return new FileNameComparator(nextComparator);
            default:
                return DEFAULT_COMPARATOR;
        }
    }
}
