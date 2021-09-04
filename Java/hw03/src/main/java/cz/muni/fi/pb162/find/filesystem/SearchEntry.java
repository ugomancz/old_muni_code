package cz.muni.fi.pb162.find.filesystem;

import java.nio.file.Path;

/**
 * Abstract class that represents search entry. The purpose of this abstraction is to isolate and simplify some
 * of the capabilities provided by {@link  java.nio.file.Path} and {@link java.io.File}
 *
 * See {@link DirEntry} and {@link FileEntry}
 *
 * @author pstanko
 */
public abstract class SearchEntry {

    private Path path;
    private long size;

    /**
     * Constructor for SearchEntry class.
     */
    public SearchEntry() {
    }

    /**
     * Constructor for SearchEntry class.
     *
     * @param path Path object wrapped by this entry
     */
    public SearchEntry(Path path) {
        this.path = path;
    }

    public Path getPath() {
        return path;
    }

    public void setPath(Path path) {
        this.path = path;
    }

    /**
     * see {@link Path#getFileName()}
     *
     * @return name of file or directory
     */
    public Path getFileName() {
        return path.getFileName();
    }

    /**
     * @return total size of file or directory
     */
    public long getSize() {
        return size;
    }

    public void setSize(long size) {
        this.size = size;
    }

    /**
     * @return type of Search entry
     */
    public abstract Types getType();

    @Override
    public String toString() {
        return path + " [" + size + "]";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (!(o instanceof SearchEntry)) {
            return false;
        }

        SearchEntry that = (SearchEntry) o;

        return this.getType() == that.getType() && (getPath() != null ?
            getPath().equals(that.getPath()) :
            that.getPath() == null);

    }

    @Override
    public int hashCode() {
        return getPath() != null ? getPath().hashCode() : 0;
    }

    /**
     * Types of entities in directory
     */
    public enum Types {
        FILE, DIR, BOTH
    }
}
