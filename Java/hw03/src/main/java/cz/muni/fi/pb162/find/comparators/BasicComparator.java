package cz.muni.fi.pb162.find.comparators;

import java.util.Comparator;

import cz.muni.fi.pb162.find.filesystem.SearchEntry;

/**
 * BasicComparator interface that all of yours custom comparators should implement
 * Next comparator is an instance of comparator that will be used
 * when the result of compare is zero, a.k.a entities are equal.
 *
 * @author pstanko
 */
public interface BasicComparator extends Comparator<SearchEntry> {
    /**
     * Returns reference to next comparator
     *
     * @return Next comparator or null if there is any
     */
    BasicComparator getNextComparator();
}
