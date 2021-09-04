package cz.muni.fi.pb162.find.impl.comparators;

import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import cz.muni.fi.pb162.find.comparators.BasicComparator;
import cz.muni.fi.pb162.find.tools.SortFactory;
import org.junit.Test;

/**
 * @author pstanko
 */
public class SortFactoryTest {
    @Test
    public void shouldCreateDefault() throws Exception {
        BasicComparator comp = SortFactory.create("");
        assertTrue("Comparator should be instance of FilePathComparator",comp instanceof FilePathComparator);
        assertNull("Next comparator should be null",comp.getNextComparator());
    }

    @Test
    public void shouldCreateFileName() throws Exception {
        BasicComparator comp = SortFactory.create("n");
        assertTrue("Comparator should be instance of FileNameComparator",comp instanceof FileNameComparator);
        assertTrue("Next comparator should be instance of FilePathComparator", comp.getNextComparator() instanceof FilePathComparator);
    }

    @Test
    public void shouldCreateExtention() throws Exception {
        BasicComparator comp = SortFactory.create("e");
        assertTrue("Comparator should be instance of FileExtensionComparator",comp instanceof FileExtensionComparator);
        assertTrue("Next comparator should be instance of FilePathComparator",comp.getNextComparator() instanceof FilePathComparator);
    }

    @Test
    public void shouldCreateFileSizeComparator() throws Exception {
        BasicComparator comp = SortFactory.create("s");
        assertTrue("Comparator should be instance of FileSizeComparator", comp instanceof FileSizeComparator);
        assertTrue("Next comparator should be instance of FilePathComparator",comp.getNextComparator() instanceof FilePathComparator);
    }

    @Test
    public void shouldCreatePathComparator() throws Exception {
        BasicComparator comp = SortFactory.create("f");
        assertTrue("Comparator should be instance of FilePathComparator",comp instanceof FilePathComparator);
        assertNull("Next comparator should be null" ,comp.getNextComparator());
    }

    @Test
    public void shouldCreateMultipleComparators() throws Exception {
        BasicComparator comp = SortFactory.create("esn");
        assertTrue("Comparator should be instance of FileExtensionComparator", comp instanceof FileExtensionComparator);
        BasicComparator bc = comp;
        assertTrue("Next comparator should be instance of FileSizeComparator", bc.getNextComparator() instanceof FileSizeComparator);

        bc = bc.getNextComparator();
        assertTrue("Next next comparator should be instance of FileNameComparator", bc.getNextComparator() instanceof FileNameComparator);

        bc = bc.getNextComparator();
        assertTrue("Next next next comparator should be instance of FilePathComparator", bc.getNextComparator() instanceof FilePathComparator);
    }


}
