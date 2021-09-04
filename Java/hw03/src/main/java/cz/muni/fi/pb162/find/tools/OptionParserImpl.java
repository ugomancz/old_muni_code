package cz.muni.fi.pb162.find.tools;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;

/**
 * Created by pstanko.
 *
 * @author pstanko
 */
public class OptionParserImpl implements OptionParser {

    private Map<String, String> parsedOptions;
    private List<String> progArgs;

    private static void usage(Options options) {
        String header = "My super simple find\n\n";
        String footer = "\nPlease report issues at stanko@mail.muni.cz";

        HelpFormatter formatter = new HelpFormatter();
        formatter.printHelp("find.jar", header, options, footer, true);
    }

    private Options initOptions() {
        Options options = new Options();

        options.addOption(optionDir());
        options.addOption(optionFileText());
        options.addOption(optionName());
        options.addOption(optionSizeMax());
        options.addOption(optionSizeMin());
        options.addOption(optionSort());
        options.addOption(optionHelp());
        options.addOption(optionType());
        return options;
    }

    @Override
    public Map<String, String> parse(String[] args) {
        parsedOptions = new HashMap<>();
        CommandLineParser parser = new DefaultParser();
        Options options = initOptions();

        try {
            CommandLine cmd = parser.parse(options, args);

            if (cmd.hasOption("help")) {
                usage(options);
                System.exit(0);
            }

            for (Option o : cmd.getOptions()) {
                System.out.println("Passed option: " + o.getLongOpt());
                if (o.getValue() != null) {
                    System.out.println("\twith value: " + o.getValue());
                    parsedOptions.put(o.getArgName(), o.getValue().trim());
                }
            }

            progArgs = cmd.getArgList();

        } catch (ParseException e) {
            System.err.println("Error parsing command line options");
            System.err.println(e.getMessage());
            usage(options);
            System.exit(1);
        }

        return parsedOptions;
    }

    @Override
    public Map<String, String> getOptions() {
        return parsedOptions;
    }

    @Override
    public List<String> getArguments() {
        return progArgs;
    }

    private Option optionHelp() {
        return Option.builder("h")
                .argName("help")
                .longOpt("help")
                .desc("Show help")
                .build();
    }

    private Option optionDir() {
        return Option.builder("d")
                .argName(OPT_DIR)
                .longOpt(OPT_DIR)
                .hasArg()
                .desc("Directory from which to start")
                .build();
    }

    private Option optionType() {
        return Option.builder("t")
                .argName(OPT_TYPE)
                .longOpt(OPT_TYPE)
                .hasArg()
                .desc("File type (file|sym|dir|other)")
                .build();
    }

    private Option optionName() {
        return Option.builder("n")
                .argName(OPT_NAME)
                .longOpt(OPT_NAME)
                .hasArg()

                .desc("File name regex")
                .build();
    }

    private Option optionSizeMax() {
        return Option.builder("M")
                .argName(OPT_SIZE_MAX)
                .longOpt(OPT_SIZE_MAX)
                .hasArg()
                .desc("Maximum file size")
                .build();
    }

    private Option optionSizeMin() {
        return Option.builder("m")
                .argName(OPT_SIZE_MIN)
                .longOpt(OPT_SIZE_MIN)
                .hasArg()
                .desc("Minimum file size")
                .build();
    }

    private Option optionFileText() {
        return Option.builder("T")
                .argName(OPT_TEXT)
                .longOpt(OPT_TEXT)
                .hasArg()
                .desc("Minimum file size")
                .build();
    }

    private Option optionSort() {
        return Option.builder("s")
                .argName(OPT_SORT)
                .longOpt(OPT_SORT)
                .hasArg()
                .desc("Sort by optionList")
                .build();
    }

}
