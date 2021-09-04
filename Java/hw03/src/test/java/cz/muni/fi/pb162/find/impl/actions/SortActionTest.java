package cz.muni.fi.pb162.find.impl.actions;

import static cz.muni.fi.pb162.find.TestUtils.createFile;
import static cz.muni.fi.pb162.find.TestUtils.parseOptions;
import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.List;

import cz.muni.fi.pb162.find.ApplicationOptions;
import cz.muni.fi.pb162.find.actions.SortAction;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import org.junit.Test;

/**
 * @author pstanko
 */
public class SortActionTest {
    @Test
    public void shouldSortBySize() throws Exception {

        ApplicationOptions applicationOptions = parseOptions("-s s");
        SortAction action = new SortActionImpl(applicationOptions);

        SearchEntry f1 = createFile("a", 1);
        SearchEntry f2 = createFile("a/a", 10);
        SearchEntry f3 = createFile("a.a", 2);
        SearchEntry f4 = createFile(".a.a/.a.a", 30);
        SearchEntry f5 = createFile("./.a.a/.aa.a", 5);

        List<SearchEntry> unsorted = new ArrayList<>();
        unsorted.add(f1);
        unsorted.add(f2);
        unsorted.add(f3);
        unsorted.add(f4);
        unsorted.add(f5);
        List<SearchEntry> sorted  = action.sorted(unsorted);


        assertEquals("Failed on index 0", f1, sorted.get(0));
        assertEquals("Failed on index 1", f3, sorted.get(1));
        assertEquals("Failed on index 2", f5, sorted.get(2));
        assertEquals("Failed on index 3", f2, sorted.get(3));
        assertEquals("Failed on index 4", f4, sorted.get(4));
    }

    @Test
    public void ShouldSortBySizeAndExtension() throws Exception {

        ApplicationOptions applicationOptions = parseOptions("-s se");
        SortAction action = new SortActionImpl(applicationOptions);

        SearchEntry f1 = createFile("a", 1); // 0
        SearchEntry f2 = createFile("a.a", 1); // 1
        SearchEntry f3 = createFile("./.a.a/.aa.aaa", 10); // 4
        SearchEntry f4 = createFile("a/a", 10); // 2
        SearchEntry f5 = createFile("a.a/.a.a", 10); // 3

        List<SearchEntry> unsorted = new ArrayList<>();
        unsorted.add(f1);
        unsorted.add(f2);
        unsorted.add(f3);
        unsorted.add(f4);
        unsorted.add(f5);
        List<SearchEntry> sorted  = action.sorted(unsorted);
        System.out.println(sorted);

        assertEquals("Failed on index 0", f1, sorted.get(0));
        assertEquals("Failed on index 1", f2, sorted.get(1));
        assertEquals("Failed on index 2", f4, sorted.get(2));
        assertEquals("Failed on index 3", f5, sorted.get(3));
        assertEquals("Failed on index 4", f3, sorted.get(4));
    }

}
