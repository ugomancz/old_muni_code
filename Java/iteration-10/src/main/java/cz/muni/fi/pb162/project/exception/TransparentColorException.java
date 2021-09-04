package cz.muni.fi.pb162.project.exception;

/**
 * Exception when color of pen is the same as the color of the paper
 *
 * @author Ondrej Kostik
 */
public class TransparentColorException extends Exception {
    /**
     * Constructor with message
     *
     * @param message is the message
     */
    public TransparentColorException(String message) {
        super(message);
    }

    /**
     * Constructor with message and cause
     *
     * @param message is the message
     * @param cause is the cause
     */
    public TransparentColorException(String message, Throwable cause) {
        super(message, cause);
    }
}