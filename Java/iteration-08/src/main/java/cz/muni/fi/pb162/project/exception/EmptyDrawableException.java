package cz.muni.fi.pb162.project.exception;

/**
 * Nothing drawn on the canvas
 *
 * @author Ondrej Kostik
 */
public class EmptyDrawableException extends Exception {
    /**
     * Constructor with message
     *
     * @param message is the message
     */
    public EmptyDrawableException(String message) {
        super(message);
    }

    /**
     * Constructor with message and cause
     *
     * @param message is the message
     * @param cause cause is the cause
     */
    public EmptyDrawableException(String message, Throwable cause) {
        super(message, cause);
    }
}
