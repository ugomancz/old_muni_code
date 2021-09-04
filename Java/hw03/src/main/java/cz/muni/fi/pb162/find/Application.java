package cz.muni.fi.pb162.find;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.Map;

import cz.muni.fi.pb162.find.actions.FilterAction;
import cz.muni.fi.pb162.find.actions.SortAction;
import cz.muni.fi.pb162.find.exceptions.SimpleSearchException;
import cz.muni.fi.pb162.find.filesystem.FSWalkResult;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import cz.muni.fi.pb162.find.impl.FSWalkResultImpl;
import cz.muni.fi.pb162.find.impl.actions.FilterActionImpl;
import cz.muni.fi.pb162.find.impl.actions.SortActionImpl;
import cz.muni.fi.pb162.find.tools.OptionParser;
import cz.muni.fi.pb162.find.tools.OptionParserImpl;

/**
 * Main class this is executable class that holds implementation of program
 * You can run it.
 *
 * @author pstanko
 */
public class Application {

    /**
     * Private variable that holds application options
     */
    private ApplicationOptions options;

    /**
     * Creates an instance of Application
     * @param args Arguments passed to an application
     */
    public Application(String[] args) {
        OptionParser parser = new OptionParserImpl();
        Map<String, String> optsMap = parser.parse(args);
        options = new ApplicationOptionsImpl(optsMap);

        System.out.println(options);
    }

    /**
     * Creates a instance of Application and runs it
     *
     * @param args Arguments of the program
     */
    public static void main(String[] args) {
        new Application(args).run();
    }


    /**
     * Runs the Application
     */
    public void run() {

        FSWalkResult walker;

        try {
            walker = walk();
        } catch (SimpleSearchException e) {
            System.err.println("Error occurred: " + e);
            return;
        }

        switch (options.getType()) {
            case DIR:
                processAndPrintEntries("Directories: ", walker.getDirectories());
                break;
            case BOTH:
                processAndPrintEntries("Directories: ", walker.getDirectories());
            case FILE:
                processAndPrintEntries("Files: ", walker.getFiles());
                break;
        }
    }
    /**
     * Prints list of paths
     *
     * @param entries List of paths that will be printed
     */
    private void printEntries(List<SearchEntry> entries) {
        entries.forEach(System.out::println);
    }

    /**
     * Sorts entries
     * @param entries
     * @return
     */
    private List<SearchEntry> sortEntries(List<SearchEntry> entries) {
        SortAction sort = new SortActionImpl(options);
        return sort.sorted(entries);
    }

    /**
     * Filters entries
     * @param entries
     * @return
     */
    private List<SearchEntry> filterEntries(List<SearchEntry> entries) {
        FilterAction filterAction = new FilterActionImpl(options);
        return filterAction.filter(entries);
    }

    /**
     * Apply filter, sort and print entries
     * @param entries List of entries that will be printed
     */
    private void processAndPrintEntries(String label, List<SearchEntry> entries) {
        System.out.println(label);
        entries = filterEntries(entries);
        entries = sortEntries(entries);
        printEntries(entries);
    }

    /**
     * Function that calls walkFileTree() from start directory using instance of your implementation of visitor
     *
     * @return Instance of FSWalkResult
     * @throws SimpleSearchException when any error occurs
     */
    private FSWalkResult walk() throws SimpleSearchException {
        FSWalkResultImpl visitor = new FSWalkResultImpl(options);
        try {
            Files.walkFileTree(Paths.get(options.getDirectory()), visitor);
        } catch (IOException e) {
            throw new SimpleSearchException("Unable to search directory: " + options.getDirectory(), e);
        }
        return visitor;
    }

}
