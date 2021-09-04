package cz.muni.fi.pb162.find.impl.filters;

import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import cz.muni.fi.pb162.find.filters.BasicFilter;

import java.io.IOException;
import java.nio.file.Files;
import java.util.List;

/**
 * filter based on the content of a file
 * <p>
 * Assignment for FileContentFilter wasn't very specific and provided tests are empty,
 * but I imagine it would work similarly to this
 *
 * @author Ondrej Kostik
 */
public class FileContentFilter extends BasicFilter {
    private String regex;

    /**
     * constructor
     *
     * @param paths list of entries to filter
     * @param regex regex to look for in file content
     */
    public FileContentFilter(List<SearchEntry> paths, String regex) {
        super(paths);
        this.regex = regex;
    }

    @Override
    public boolean filter(SearchEntry path) {
        try {
            String allLines = new String(Files.readAllBytes(path.getPath()));
            return allLines.matches(regex);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return false;
    }
}
