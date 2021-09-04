package cz.muni.fi.pb162.find.impl.filters;

import static cz.muni.fi.pb162.find.TestUtils.createFile;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;

import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import cz.muni.fi.pb162.find.filters.BasicFilter;
import org.junit.Test;

/**
 * @author pstanko
 */
public class MinSizeFilterActionTest {
    private static final long Threshold = 200;
    private static BasicFilter filter = new MinSizeFilter(new ArrayList<SearchEntry>(), Threshold);

    private static void testTrue(SearchEntry what)
    {
        assertTrue("Filtered file \"" + what + "\" less than threshold (" +  Threshold +").", filter.filter(what));
    }

    private static void testFalse(SearchEntry what)
    {
        assertFalse("Not filtered file \"" + what + "\" less than threshold (" +  Threshold +").", filter.filter(what));
    }

    @Test
    public void shouldAddGreaterThanThreshold() throws Exception {
        SearchEntry se = createFile("ahoj", 120);
        testFalse(se);
    }

    @Test
    public void shouldNotAddLessThanThreshold() throws Exception {
        SearchEntry se = createFile("ahoj", 220);
        testTrue(se);
    }

    @Test
    public void shouldAddEqualsToThreshold() throws Exception {
        SearchEntry se = createFile("ahoj", Threshold);
        testTrue(se);
    }
}
