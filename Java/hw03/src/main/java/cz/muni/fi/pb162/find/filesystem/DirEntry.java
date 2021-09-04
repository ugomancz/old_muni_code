package cz.muni.fi.pb162.find.filesystem;

import java.nio.file.Path;

/**
 * @author pstanko
 */
public class DirEntry extends SearchEntry {

    /**
     * Constructor for DirEntry class.
     *
     * @param path Path object wrapped by this entry
     */
    public DirEntry(Path path) {
        super(path);
    }

    @Override
    public Types getType() {
        return Types.DIR;
    }

    @Override
    public String toString() {
        return "D " + super.toString();
    }
}
