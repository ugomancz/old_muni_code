package cz.muni.fi.pb162.find.impl.filters;

import static cz.muni.fi.pb162.find.TestUtils.createFile;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;

import cz.muni.fi.pb162.find.filters.BasicFilter;
import org.junit.Test;

/**
 * @author pstanko
 */
public class FileNameFilterActionTest {

    private static void testTrue(String what, String regex)
    {
        BasicFilter filter = new FileNameFilter(new ArrayList<>(), regex);
        assertTrue("Filtered \"" + what + "\" for \""+ regex +"\" regex." ,filter.filter(createFile(what)));
    }

    private static void testFalse(String what, String regex)
    {
        BasicFilter filter = new FileNameFilter(new ArrayList<>(), regex);
        assertFalse("Not filtered \"" + what + "\" for \""+ regex +"\" regex." ,filter.filter(createFile(what)));
    }


    @Test
    public void shouldAddExactMatch() throws Exception {
        final String regex = "ahoj";
        testTrue("ahoj", regex);
        testFalse("aho", regex);
        testFalse("ahoj1", regex);
        testFalse("Ahoj", regex);
    }

    @Test
    public void shouldAddPrefixAhoj() throws Exception {
        final String regex = "ahoj.*";
        testTrue("ahoj", regex);
        testFalse("aho", regex);
        testTrue("ahoj1", regex);
        testFalse("Ahoj", regex);
        testFalse("zahoj", regex);
    }

    @Test
    public void shouldAddSuffixAhoj() throws Exception {
        final String regex = ".*ahoj";
        testTrue("ahoj", regex);
        testFalse("aho", regex);
        testFalse("ahoj1", regex);
        testFalse("Ahoj", regex);
        testTrue("zahoj", regex);
    }

}
