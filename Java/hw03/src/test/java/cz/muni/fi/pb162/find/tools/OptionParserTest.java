package cz.muni.fi.pb162.find.tools;

import static cz.muni.fi.pb162.find.tools.OptionParser.*;
import static org.junit.Assert.assertEquals;

import java.util.Map;

import cz.muni.fi.pb162.find.tools.OptionParser;
import cz.muni.fi.pb162.find.tools.OptionParserImpl;
import org.apache.tools.ant.types.Commandline;
import org.junit.Test;

/**
 * @author pstanko
 */
public class OptionParserTest {

    private static Map<String, String> parse(String str) {
        String[] args = Commandline.translateCommandline(str);
        OptionParser op = new OptionParserImpl();
        return op.parse(args);
    }

    @Test()
    public void shouldParseEmpty() throws Exception {
        assertEquals(0, parse("").size());
    }

    @Test()
    public void shouldParseType() throws Exception {
        Map<String, String> parsedArgs = parse("-t FILE");
        assertEquals(1, parsedArgs.size());
        assertEquals("FILE", parsedArgs.get("type"));

        parsedArgs = parse("--type \"FILE\"");
        assertEquals(1, parsedArgs.size());
        assertEquals("FILE", parsedArgs.get(OPT_TYPE));
    }

    @Test()
    public void shouldParseDirectory() throws Exception {
        Map<String, String> parsedArgs = parse("-d /dev");
        assertEquals(1, parsedArgs.size());
        assertEquals("/dev", parsedArgs.get(OPT_DIR));

        parsedArgs = parse("--dir \"/dev\"");
        assertEquals(1, parsedArgs.size());
        assertEquals("/dev", parsedArgs.get(OPT_DIR));
    }
}
