package cz.muni.fi.pb162.find.tools;

import static cz.muni.fi.pb162.find.TestUtils.parseOptions;
import static org.junit.Assert.assertEquals;

import cz.muni.fi.pb162.find.ApplicationOptions;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import org.junit.Assert;
import org.junit.Test;

/**
 * @author pstanko
 */
public class ApplicationOptionsTest {




    @Test
    public void shouldGetCorrectDefaultValues() throws Exception {
        ApplicationOptions opts = parseOptions("");
        Assert.assertEquals(SearchEntry.Types.BOTH, opts.getType());
        assertEquals(".", opts.getDirectory());
        assertEquals(null, opts.getNameRegex());
        assertEquals(null, opts.getTextRegex());
        assertEquals(null, opts.getSizeMax());
        assertEquals(null, opts.getSizeMin());
        assertEquals("f", opts.getSort());
    }

    @Test
    public void shouldSetCorrectDefaultDir() throws Exception {
        ApplicationOptions opts = parseOptions("-d \"/dev/\"");
        assertEquals(SearchEntry.Types.BOTH, opts.getType());
        assertEquals("/dev/", opts.getDirectory());
        assertEquals(null, opts.getNameRegex());
        assertEquals(null, opts.getTextRegex());
        assertEquals(null, opts.getSizeMax());
        assertEquals(null, opts.getSizeMin());
        assertEquals("f", opts.getSort());
    }

    @Test
    public void shouldShowAll() throws Exception {
        ApplicationOptions opts = parseOptions("");
        assertEquals(SearchEntry.Types.BOTH, opts.getType());
        assertEquals(".", opts.getDirectory());
        assertEquals(null, opts.getNameRegex());
        assertEquals(null, opts.getTextRegex());
        assertEquals(null, opts.getSizeMax());
        assertEquals(null, opts.getSizeMin());
        assertEquals("f", opts.getSort());
    }

    @Test
    public void shouldGetFileType() throws Exception {
        ApplicationOptions opts = parseOptions("-t file");
        assertEquals(SearchEntry.Types.FILE, opts.getType());
        assertEquals(".", opts.getDirectory());
        assertEquals(null, opts.getNameRegex());
        assertEquals(null, opts.getTextRegex());
        assertEquals(null, opts.getSizeMax());
        assertEquals(null, opts.getSizeMin());
        assertEquals("f", opts.getSort());
    }

    @Test
    public void shouldShowDirectories() throws Exception {
        ApplicationOptions opts = parseOptions("-t DIR");
        assertEquals(SearchEntry.Types.DIR, opts.getType());
        assertEquals(".", opts.getDirectory());
        assertEquals(null, opts.getNameRegex());
        assertEquals(null, opts.getTextRegex());
        assertEquals(null, opts.getSizeMax());
        assertEquals(null, opts.getSizeMin());
        assertEquals("f", opts.getSort());
    }

    @Test
    public void shouldReturnValidMinSize() throws Exception {
        ApplicationOptions opts = parseOptions("-m 100");
        assertEquals(SearchEntry.Types.BOTH, opts.getType());
        assertEquals(".", opts.getDirectory());
        assertEquals(null, opts.getNameRegex());
        assertEquals(null, opts.getTextRegex());
        assertEquals(null, opts.getSizeMax());
        assertEquals(new Long(100L), opts.getSizeMin());
        assertEquals("f", opts.getSort());
    }

    @Test
    public void shouldReturnValidSort() throws Exception {
        ApplicationOptions opts = parseOptions("-s esf");
        assertEquals(SearchEntry.Types.BOTH, opts.getType());
        assertEquals(".", opts.getDirectory());
        assertEquals(null, opts.getNameRegex());
        assertEquals(null, opts.getTextRegex());
        assertEquals(null, opts.getSizeMax());
        assertEquals(null, opts.getSizeMin());
        assertEquals("esf", opts.getSort());
    }

    @Test
    public void shouldHaveMultiple() throws Exception {
        ApplicationOptions opts = parseOptions("--type=FILE -d /dev -s esf");
        assertEquals(SearchEntry.Types.FILE, opts.getType());
        assertEquals("/dev", opts.getDirectory());
        assertEquals(null, opts.getNameRegex());
        assertEquals(null, opts.getTextRegex());
        assertEquals(null, opts.getSizeMax());
        assertEquals(null, opts.getSizeMin());
        assertEquals("esf", opts.getSort());
    }
}
