package cz.muni.fi.pb162.find;

import cz.muni.fi.pb162.find.filesystem.*;
import cz.muni.fi.pb162.find.tools.OptionParser;
import cz.muni.fi.pb162.find.tools.OptionParserImpl;
import org.apache.tools.ant.types.Commandline;

import java.nio.file.Paths;
import java.util.Map;

/**
 * @author pstanko
 */
public class TestUtils {

    public static ApplicationOptions parseOptions(String str) {
        String[] args = Commandline.translateCommandline(str);
        OptionParser op = new OptionParserImpl();
        Map<String, String> parse = op.parse(args);
        return new ApplicationOptionsImpl(parse);
    }

    public static SearchEntry createFile(String name) {
        return createFile(name, 0, false);
    }

    public static SearchEntry createFile(String name, long size) {
        return createFile(name, size, false);
    }

    public static SearchEntry createFile(String name, boolean hid) {
        return createFile(name, 0, hid);
    }

    public static SearchEntry createDir(String name) {
        return createDir(name, 0, false);
    }

    public static SearchEntry createDir(String name, long size) {
        return createDir(name, size, false);
    }

    public static SearchEntry createDir(String name, boolean hid) {
        return createDir(name, 0, hid);
    }

    public static SearchEntry createFile(String name, long size, boolean hid) {
        SearchEntry ent = new FileEntry(Paths.get(name));
        ent.setSize(size);
        return ent;
    }

    public static SearchEntry createDir(String name, long size, boolean hid) {
        SearchEntry ent = new DirEntry(Paths.get(name));
        ent.setSize(size);
        return ent;
    }
}
