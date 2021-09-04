package cz.muni.fi.pb162.project.geometry;

/**
 * @author Ondrej Kostik
 */
public enum Color {
    WHITE,
    YELLOW,
    ORANGE,
    RED,
    BLUE,
    GREEN,
    BLACK;
    @Override
    public String toString(){
        return this.name().toLowerCase();
    }
}
