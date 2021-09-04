package cz.muni.fi.pb162.find.impl;

import cz.muni.fi.pb162.find.ApplicationOptions;
import cz.muni.fi.pb162.find.filesystem.DirEntry;
import cz.muni.fi.pb162.find.filesystem.FSWalkResult;
import cz.muni.fi.pb162.find.filesystem.FileEntry;
import cz.muni.fi.pb162.find.filesystem.SearchEntry;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Implementation of FSWalkResult
 *
 * @author Ondrej Kostik
 */
public class FSWalkResultImpl extends FSWalkResult {
    /**
     * Constructor for class FSWalkResult
     *
     * @param options application options
     */
    public FSWalkResultImpl(ApplicationOptions options) {
        super(options);
    }

    @Override
    public List<SearchEntry> getDirectories() {
        List<SearchEntry> result = new ArrayList<>();
        try {
            List<Path> files = Files.walk(Paths.get(getOpts().getDirectory()))
                    .filter(Files::isDirectory)
                    .collect(Collectors.toList());
            for (Path path : files) {
                DirEntry newDirEntry = new DirEntry(path);
                newDirEntry.setSize(Files.size(path));
                result.add(newDirEntry);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }

    @Override
    public List<SearchEntry> getFiles() {
        List<SearchEntry> result = new ArrayList<>();
        try {
            List<Path> filesInFolder = Files.walk(Paths.get(getOpts().getDirectory()))
                    .filter(Files::isRegularFile)
                    .collect(Collectors.toList());
            for (Path path : filesInFolder) {
                FileEntry newFileEntry = new FileEntry(path);
                newFileEntry.setSize(Files.size(path));
                result.add(newFileEntry);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }
}
