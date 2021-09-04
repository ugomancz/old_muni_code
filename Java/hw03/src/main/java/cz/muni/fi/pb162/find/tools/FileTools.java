package cz.muni.fi.pb162.find.tools;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

/**
 * Do not modify implemented methods but you can add yous!
 *
 * @author pstanko
 */
public class FileTools {

    /**
     * Returns file extension for a file, if file has no extension returns null
     * Special case - file is hidden - if file starts with dot and there is no other dot,
     * that file has no extension.
     * ex1. (".config_file") - it is hidden file, with name ".config_file" but with no extension
     * ex2. (".config.file") - it is a hidden file, with name ".config.file" but with extension "file"
     * ---
     * Use this function to get extension from a file
     *
     * @param path Path to file
     * @return extension if there is some, null if not
     */
    public static String fileExtension(Path path) {
        String fileName = path.getFileName().toString();
        if (fileName.startsWith(".") && fileName.indexOf('.') == fileName.lastIndexOf(".")) {
            return null;
        }
        if (fileName.lastIndexOf(".") != -1 && fileName.lastIndexOf(".") != 0) {
            return fileName.substring(fileName.lastIndexOf(".") + 1);
        } else {
            return null;
        }
    }

    /**
     * Returns the size of file or the total size of a directory . The size of directory is equal to
     * the sum of sizes of files in that directory and all its subdirectories.
     *
     * @param path file/directory path
     * @return total size of all entries on given path
     */
    public static long dirSize(Path path) {
        try {
            return Files.walk(path)
                .filter(p -> p.toFile().isFile())
                .mapToLong(p -> p.toFile().length())
                .sum();
        } catch (IOException e) {
            return 0L;
        }
    }
}
