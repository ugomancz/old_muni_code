package cz.muni.fi.pb162.find.impl.comparators;

import static cz.muni.fi.pb162.find.TestUtils.createFile;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import cz.muni.fi.pb162.find.comparators.BasicComparator;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import cz.muni.fi.pb162.find.tools.SortFactory;
import org.junit.Test;

/**
 * @author pstanko
 */
public class FileExtensionComparatorTest {

    private static BasicComparator se = SortFactory.create("e");

    private static void testEquals(String path){
        assertEquals( "Files with same extension are not equal." ,0, se.compare(createFile(path), createFile(path)));
    }

    private static void testTrue(String p1, String p2) {
        SearchEntry first = createFile(p1);
        SearchEntry second = createFile(p2);
        String message = "File \"" + first + "\" should be greater than \"" + second + "\".";
        assertTrue(message,se.compare(first, second) > 0);
    }

    @Test
    public void shouldCompareSimpleFiles() throws Exception {
        testTrue("ahoj.svet", "ahoj.jpg");
        testEquals("ahoj.jpg");
    }

    @Test
    public void shouldCompareWithoutExtention() throws Exception {
        testTrue("ahoj3", "ahoj");
        testEquals("ahoj");
    }

    @Test
    public void shouldCompareLongPath() throws Exception {
        String first = ("ahoj/ahoj/ahoj.jpg");
        String second = ("ahoj/ahoj/ahoj.png");
        testTrue(second, first);
        testEquals("ahoj/ahoj.jpg");

    }

}
