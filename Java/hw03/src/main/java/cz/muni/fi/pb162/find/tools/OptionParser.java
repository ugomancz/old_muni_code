package cz.muni.fi.pb162.find.tools;

import java.util.List;
import java.util.Map;

/**
 * Helper class that will parse
 *
 * @author pstanko
 */
public interface OptionParser {

    String OPT_DIR = "dir";
    String OPT_NAME = "name";
    String OPT_TYPE = "type";
    String OPT_SIZE_MAX = "size-max";
    String OPT_SIZE_MIN = "size-min";
    String OPT_TEXT = "text";
    String OPT_SORT = "sort";

    /**
     * Parse arguments passed to command line
     *
     * @param args Command line arguments
     * @return Parsed map of arguments
     */
    Map<String, String> parse(String[] args);

    /**
     * Get Options
     *
     * @return Collection of options (name and value)
     */
    Map<String, String> getOptions();

    /**
     * Get arguments that are not bind to any option
     *
     * @return List of arguments
     */
    List<String> getArguments();
}
