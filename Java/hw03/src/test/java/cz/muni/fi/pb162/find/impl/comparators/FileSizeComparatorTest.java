package cz.muni.fi.pb162.find.impl.comparators;

import static cz.muni.fi.pb162.find.TestUtils.createDir;
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
public class FileSizeComparatorTest {
    private static BasicComparator se = SortFactory.create("s");

    private static void testEquals(long size){
        assertEquals( "Files with same names are not equal." ,0,
            se.compare(createFile("test", size), createFile("test", size)));
    }

    private static void testEqualDirs(long size){
        assertEquals( "Dirs with same names are not equal." ,0,
            se.compare(createDir("test", size), createDir("test", size)));
    }

    private static void testFile(long s1, long s2){
        SearchEntry first = createFile("test", s1);
        SearchEntry second = createFile("test", s2);
        String message = "File \"" + first + "\" should be greater than \"" + second + "\".";
        assertTrue(message,se.compare(first, second) > 0);
    }

    private static void testDir(long s1, long s2){
        SearchEntry first = createDir("test", s1);
        SearchEntry second = createDir("test", s2);
        String message = "Dir \"" + first + "\" should be greater than \"" + second + "\".";
        assertTrue(message,se.compare(first, second) > 0);
    }


    @Test
    public void shouldCompareFileSizes() throws Exception {
        testFile(20, 10);
        testEquals(100);
        testEquals(0);
    }

    @Test
    public void shouldCompareSimpleDirs() throws Exception {
        testDir(20, 10);
        testEqualDirs(100);
        testEqualDirs(0);
    }

}
