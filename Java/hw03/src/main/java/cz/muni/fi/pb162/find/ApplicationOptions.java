package cz.muni.fi.pb162.find;

import cz.muni.fi.pb162.find.filesystem.SearchEntry;

/**
 * Applications options interface, it will provide only getters for specified variables
 *
 * @author pstanko
 */
public interface ApplicationOptions {


    /**
     * Get directory to start from
     *
     * @return path to directory to start from
     */
    String getDirectory();

    /**
     * Get file name regex to be filtered by
     *
     * @return filename regex
     */
    String getNameRegex();

    /**
     * Get text regex in file to be filtered by
     *
     * @return text regex
     */
    String getTextRegex();

    /**
     * Get entry type that should be printed
     * When BOTH - you are printing Directories first, then Files
     *
     * @return enum of entry types
     */
    SearchEntry.Types getType();

    /**
     * Maximum file size, greater should be filtered
     *
     * @return maximum file size, null if filter should not be applied
     */
    Long getSizeMax();

    /**
     * Minimum file size, lesser should be filtered
     *
     * @return minimal file size, null if filter should not be applied
     */
    Long getSizeMin();

    /**
     * Sort order
     *
     * f - sort by path (default)
     * s - sort by size
     * e - sort by extension
     * n - sort by name (the last fragment of path)
     *
     * Example: "fes" means that the order of entries should be determined first by path, then by extension,
     *          and then finally by size.
     *
     *
     * @return sort order string
     */
    String getSort();
}
