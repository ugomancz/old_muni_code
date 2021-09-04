package cz.muni.fi.pb162.find.tools;

import static cz.muni.fi.pb162.find.tools.FileTools.fileExtension;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

import java.nio.file.Paths;

import org.junit.Test;

/**
 * @author pstanko
 */
public class FileToolsTest {

    @Test
    public void shouldGetCorrectFileExtension() throws Exception {
        assertEquals("txt", fileExtension(Paths.get(".myHiddenFile.txt")));
        assertNull(fileExtension(Paths.get(".myHiddenFile")));
        assertEquals("gz", fileExtension(Paths.get(".myHiddenFile.tar.gz")));
    }

}
