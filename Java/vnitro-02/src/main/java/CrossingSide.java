/**
 * @author Ondrej Kostik
 */
public enum CrossingSide {
    LEFT,
    RIGHT;

    @Override
    public String toString() {
        return this.name().toLowerCase();
    }
}
