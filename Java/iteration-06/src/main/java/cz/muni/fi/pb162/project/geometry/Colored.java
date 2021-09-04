package cz.muni.fi.pb162.project.geometry;

/**
 * @author Ondrej Kostik
 */
public interface Colored {

    /**
     * Returns object's color
     * @return Color of object based on Color enum;
     */
    Color getColor();

    /**
     * Sets color to object
     * @param color of Color enum value is the color we want to set the object to
     */
    void setColor(Color color);
}
