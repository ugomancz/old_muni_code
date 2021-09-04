package cz.muni.fi.pb162.find.impl.actions;

import cz.muni.fi.pb162.find.ApplicationOptions;
import cz.muni.fi.pb162.find.actions.FilterAction;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import cz.muni.fi.pb162.find.impl.filters.FileContentFilter;
import cz.muni.fi.pb162.find.impl.filters.FileNameFilter;
import cz.muni.fi.pb162.find.impl.filters.MaxSizeFilter;
import cz.muni.fi.pb162.find.impl.filters.MinSizeFilter;

import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

/**
 * main execution point for filtering the result of the walk over filesystem
 *
 * @author Ondrej Kostik
 */
public class FilterActionImpl implements FilterAction {
    private ApplicationOptions opts;

    /**
     * constructor
     *
     * @param opts is an ApplicationOptions instance
     */
    public FilterActionImpl(ApplicationOptions opts) {
        this.opts = opts;
    }

    @Override
    public List<SearchEntry> filter(List<SearchEntry> entries) {
        entries = maxSizeFilter(entries);
        entries = minSizeFilter(entries);
        entries = fileNameFilter(entries);
        entries = fileContentFilter(entries);
        return Collections.unmodifiableList(entries);
    }

    private List<SearchEntry> maxSizeFilter(List<SearchEntry> entries) {
        if (opts.getSizeMax() != null) {
            MaxSizeFilter maxSizeFilter = new MaxSizeFilter(entries, opts.getSizeMax());
            return entries.stream().filter(searchEntry -> maxSizeFilter.filter(searchEntry))
                    .collect(Collectors.toList());
        }
        return entries;
    }

    private List<SearchEntry> minSizeFilter(List<SearchEntry> entries) {
        if (opts.getSizeMin() != null) {
            MinSizeFilter minSizeFilter = new MinSizeFilter(entries, opts.getSizeMin());
            return entries.stream().filter(searchEntry -> minSizeFilter.filter(searchEntry))
                    .collect(Collectors.toList());
        }
        return entries;
    }

    private List<SearchEntry> fileNameFilter(List<SearchEntry> entries) {
        if (opts.getNameRegex() != null) {
            FileNameFilter fileNameFilter = new FileNameFilter(entries, opts.getNameRegex());
            return entries.stream().filter(searchEntry -> fileNameFilter.filter(searchEntry))
                    .collect(Collectors.toList());
        }
        return entries;
    }

    private List<SearchEntry> fileContentFilter(List<SearchEntry> entries) {
        if (opts.getTextRegex() != null) {
            FileContentFilter fileContentFilter = new FileContentFilter(entries, opts.getTextRegex());
            return entries.stream().filter(searchEntry -> fileContentFilter.filter(searchEntry))
                    .collect(Collectors.toList());
        }
        return entries;
    }
}