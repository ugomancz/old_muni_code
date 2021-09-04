package cz.muni.fi.pb162.find.filesystem;

import java.nio.file.Path;
import java.nio.file.SimpleFileVisitor;
import java.util.List;

import cz.muni.fi.pb162.find.ApplicationOptions;

/**
 * This class represents a collector of files/directories under specified file tree.
 *
 * By extending {@link SimpleFileVisitor} this class has the ability to traverse the filesystem.
 * Visited entries should be stored internally and {@link #getFiles()} or {@link #getDirectories()}
 * used to retrieve them.
 *
 * When creating instances of {@link SearchEntry} do not forget to initialize their properties (e.g. size
 *
 * @author pstanko
 */
public abstract class FSWalkResult extends SimpleFileVisitor<Path> {

    private final ApplicationOptions opts;

    /**
     * Constructor for class FSWalkResult
     *
     * @param options application optios
     */
    public FSWalkResult(ApplicationOptions options) {
        if (options == null) {
            throw new IllegalArgumentException("options");
        }
        this.opts = options;
    }

    /**
     * Getter for application options
     *
     * @return Application option used to initialise this object
     */
    protected ApplicationOptions getOpts() {
        return opts;
    }

    /**
     * List all directories
     *
     * @return List of all paths to subtree directories
     */
    public abstract List<SearchEntry> getDirectories();

    /**
     * List all files
     *
     * @return List of all paths to a subtree files
     */
    public abstract List<SearchEntry> getFiles();

}
