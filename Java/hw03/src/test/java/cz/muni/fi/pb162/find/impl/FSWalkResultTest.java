package cz.muni.fi.pb162.find.impl;

import static cz.muni.fi.pb162.find.TestUtils.*;
import static org.junit.Assert.*;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

import cz.muni.fi.pb162.find.ApplicationOptions;
import cz.muni.fi.pb162.find.exceptions.SimpleSearchException;
import cz.muni.fi.pb162.find.filesystem.FSWalkResult;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;
import org.junit.Test;


/**
 * Created by pstanko.
 * @author pstanko
 */
public class FSWalkResultTest {

    private final String startDir = "./tree/";
    private final String simpleDir = startDir + "simple";
    private final String oneExtDir = startDir + "one_ext";




    private static FSWalkResult getWalk(String optString) throws SimpleSearchException{
        ApplicationOptions opts = parseOptions(optString);

        FSWalkResultImpl visitor = new FSWalkResultImpl(opts);
        try {
            Files.walkFileTree(Paths.get(opts.getDirectory()), visitor);
        } catch (IOException e) {
            throw new SimpleSearchException("Unable to search directory: " + opts.getDirectory(), e);
        }
        return visitor;
    }

    private static boolean dirContains(FSWalkResult res, String path) {
        SearchEntry ent = createDir(path);
        assertNotNull("Directories should not be null!", res.getDirectories());
        assertNotEquals("Directories should not be empty!", 0,  res.getDirectories().size());
        return res.getDirectories().contains(ent);
    }

    private static boolean fileContains(FSWalkResult res, String path) {
        SearchEntry ent = createDir(path);
        assertNotNull("Files should not be null!", res.getFiles());
        assertNotEquals("Files should not be empty!", 0,  res.getFiles().size());
        return res.getFiles().contains(ent);
    }

    private static SearchEntry getFile(FSWalkResult res, String path){
        SearchEntry ent = createFile(path);
        Optional<SearchEntry> first = res.getFiles().stream().filter((file) -> file.equals(ent)).findFirst();
        assertTrue("File \"" + path + "\" should exists!", first.isPresent());
        return first.get();
    }

    private static void testFileProperties(SearchEntry entry, String stringPath) throws IOException {
        Path path = Paths.get(stringPath);
        assertTrue("File path should exist!", Files.exists(path));
        assertTrue("File path in entry should exist!", Files.exists(entry.getPath()));
        assertEquals("File size should be same!", Files.size(path), entry.getSize());
        assertEquals("Files should have same filename!", path.getFileName(), entry.getFileName());
    }

    private static void testFileProperties(FSWalkResult res, String fPath) throws IOException {
        SearchEntry ent = getFile(res, fPath);
        testFileProperties(ent, fPath);
    }

    private static List<Path> createPaths(String prefix, List<String> names){
        return names.stream().map((name) -> Paths.get(prefix, name)).collect(Collectors.toList());
    }

    private static void testPaths(FSWalkResult res, List<Path> paths) throws IOException{
        paths.forEach((path) -> {
            try {
                testFileProperties(res, path.toString());
            } catch (IOException e) {
                assertFalse(true);
                e.printStackTrace();
            }
        });

    }

    @Test
    public void shouldWalkFiles() throws Exception {
        FSWalkResult walkResult = getWalk("-d "+ simpleDir);

        assertEquals("Directories should be 1", 1, walkResult.getDirectories().size());
        assertTrue("Dirs should contains "+ simpleDir, dirContains(walkResult, simpleDir));
        assertEquals("Files should be 6", 6, walkResult.getFiles().size());

        List<String> sPaths = new ArrayList<>();
        sPaths.add("0fIle0");
        sPaths.add("_file.txt");
        sPaths.add("file.cfg");
        sPaths.add("file.t");
        sPaths.add("file.txt");

        List<Path> paths = createPaths(simpleDir, sPaths);
        testPaths(walkResult, paths);

    }

}
