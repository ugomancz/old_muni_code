package cz.muni.fi.pb162.project.exception;

/**
 * List of vertices is incomplete
 *
 * @author Ondrej Kostik
 */
public class MissingVerticesException extends RuntimeException {
    /**
     * Constructor with message
     *
     * @param message is the message
     */
    public MissingVerticesException(String message) {
        super(message);
    }

    /**
     * Constructor with message and cause
     *
     * @param message is the message
     * @param cause cause is the cause
     */
    public MissingVerticesException(String message, Throwable cause) {
        super(message, cause);
    }
}
