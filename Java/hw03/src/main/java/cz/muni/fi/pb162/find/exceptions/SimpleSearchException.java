package cz.muni.fi.pb162.find.exceptions;

import java.io.IOException;

/**
 * Exception will be thrown when any error occurs or other exception will be thrown,
 * If another exception will be thrown, you should catch it and throw SimpleSearchException
 * and pass the original exception as an argument.
 * @author pstanko
 */
public class SimpleSearchException extends IOException {

    /**
     * Constructs an {@code SimpleSearchException} with {@code null}
     * as its error detail message.
     */
    public SimpleSearchException() {
    }

    /**
     * Constructs an {@code SimpleSearchException} with the specified detail message.
     *
     * @param message
     *        The detail message (which is saved for later retrieval
     *        by the {@link #getMessage()} method)
     */
    public SimpleSearchException(String message) {
        super(message);
    }

    /**
     * Constructs an {@code SimpleSearchException} with the specified detail message
     * and cause.
     *
     * @param message
     *        The detail message (which is saved for later retrieval
     *        by the {@link #getMessage()} method)
     *
     * @param cause
     *        The cause (which is saved for later retrieval by the
     *        {@link #getCause()} method).  (A null value is permitted,
     *        and indicates that the cause is nonexistent or unknown.)
     *
     */
    public SimpleSearchException(String message, Throwable cause) {
        super(message, cause);
    }


    /**
     * Constructs an {@code SimpleSearchException} with the specified
     *
     * @param cause
     *        The cause (which is saved for later retrieval by the
     *        {@link #getCause()} method).  (A null value is permitted,
     *        and indicates that the cause is nonexistent or unknown.)
     */
    public SimpleSearchException(Throwable cause) {
        super(cause);
    }
}
