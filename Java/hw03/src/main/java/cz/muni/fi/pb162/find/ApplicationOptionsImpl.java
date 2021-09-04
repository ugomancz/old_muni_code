package cz.muni.fi.pb162.find;

import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import cz.muni.fi.pb162.find.tools.OptionParser;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by pstanko.
 *
 * @author pstanko
 */
public class ApplicationOptionsImpl implements ApplicationOptions {

    private Map<String, String> options = new HashMap<>();

    /**
     * Takes the map, parsed from Apache commons cli parser
     * @param options map containing unprocessed application options
     */
    public ApplicationOptionsImpl(Map<String, String> options) {
        this.options = new HashMap<>(options);
    }

    @Override
    public String toString() {
        return "options=" + options;
    }


    private SearchEntry.Types mapEnum(String s) {
        for (SearchEntry.Types t : SearchEntry.Types.class.getEnumConstants()) {
            if (t.name().compareToIgnoreCase(s) == 0) {
                return t;
            }
        }
        return null;
    }

    @Override
    public String getDirectory() {
        return options.getOrDefault(OptionParser.OPT_DIR, ".");
    }
    

    @Override
    public String getNameRegex() {
        return options.get(OptionParser.OPT_NAME);
    }
    
    @Override
    public String getTextRegex() {
        return options.get(OptionParser.OPT_TEXT);
    }


    @Override
    public SearchEntry.Types getType() {
        String strType = options.get(OptionParser.OPT_TYPE);
        return (strType == null) ? SearchEntry.Types.BOTH : mapEnum(strType);
    }

    @Override
    public Long getSizeMax() {
        String size = options.get(OptionParser.OPT_SIZE_MAX);
        return (size == null) ? null : Long.parseUnsignedLong(size);
    }


    @Override
    public Long getSizeMin() {
        String size = options.get(OptionParser.OPT_SIZE_MIN);
        return (size == null) ? null : Long.parseUnsignedLong(size);

    }


    public String getSort() {
        return options.getOrDefault(OptionParser.OPT_SORT, "f");
    }

}
