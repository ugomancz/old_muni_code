package cz.muni.fi.pb162.find.filesystem;

import java.nio.file.Path;

/**
 * @author pstanko
 */
public class FileEntry extends SearchEntry {


    /**
     * Constructor for FileEntry class.
     *
     * @param path Path object wrapped by this entry
     */
    public FileEntry(Path path) {
        super(path);
    }

    @Override
    public Types getType() {
        return Types.FILE;
    }

    @Override
    public String toString() {
        return "F " + super.toString();
    }
}
