package cz.muni.fi.pb162.find.impl.actions;

import static cz.muni.fi.pb162.find.TestUtils.createFile;
import static cz.muni.fi.pb162.find.TestUtils.parseOptions;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;
import java.util.List;

import cz.muni.fi.pb162.find.ApplicationOptions;
import cz.muni.fi.pb162.find.actions.FilterAction;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import org.junit.Test;

/**
 * @author pstanko
 */
public class FilterActionTest {

    private static void testContains(List<SearchEntry> entries, SearchEntry entry) {
        assertTrue("Entries should contain \"" + entry + "\".", entries.contains(entry));
    }

    private static void testNotContains(List<SearchEntry> entries, SearchEntry entry) {
        assertFalse("Entries should not contain \"" + entry + "\".", entries.contains(entry));
    }

    @Test
    public void shouldPassAllFiles() throws Exception {
        ApplicationOptions options = parseOptions("");
        List<SearchEntry> entries = new ArrayList<>();
        SearchEntry hidFile = createFile(".file1", true);
        SearchEntry pathHidFile = createFile("../file_path/.file.txt", true);
        SearchEntry normFile = createFile("file1", false);
        SearchEntry pathFile = createFile("../file_path/file.txt", false);
        SearchEntry hidPathFileListed = createFile("../.file_path/file.txt", false);

        entries.add(hidFile);
        entries.add(normFile);
        entries.add(pathFile);
        entries.add(pathHidFile);
        entries.add(hidPathFileListed);
        FilterAction action = new FilterActionImpl(options);

        List<SearchEntry> filtered = action.filter(entries);
        testContains(filtered, normFile);
        testContains(filtered, pathFile);
        testContains(filtered, (hidPathFileListed));
        testContains(filtered, hidFile);
        testContains(filtered, pathHidFile);
    }

    @Test
    public void shouldFilterBigFiles() throws Exception {
        ApplicationOptions options = parseOptions("-M 100");
        List<SearchEntry> entries = new ArrayList<>();
        SearchEntry hidFile = createFile(".file1", 100, true); // TRUE
        SearchEntry pathHidFile = createFile("../file_path/.file.txt", 10, true); // FALSE
        SearchEntry normFile = createFile("file1", 1000, false); // FALSE
        SearchEntry pathFile = createFile("../file_path/file.txt", 20, false); // TRUE
        SearchEntry hidPathFileListed = createFile("../.file_path/file.txt", 100, false); // TRUE

        entries.add(hidFile);
        entries.add(normFile);
        entries.add(pathFile);
        entries.add(pathHidFile);
        entries.add(hidPathFileListed);
        FilterAction action = new FilterActionImpl(options);

        List<SearchEntry> filtered = action.filter(entries);
        testNotContains(filtered, (normFile));
        testContains(filtered, (pathFile));
        testContains(filtered, (hidPathFileListed));
        testContains(filtered, (hidFile));
        testContains(filtered, (pathHidFile));
    }

}
