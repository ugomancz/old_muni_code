package cz.muni.fi.pb162.project.geometry;

import java.util.Objects;

/**
 * @author Ondrej Kostik
 */
public class ColoredPolygon {
    private final Polygon polygon;
    private final Color color;

    /**
     * ColoredPolygon constructor gives a Polygon a Color
     *
     * @param polygon represents a Polygon
     * @param color   represents a Color
     */
    public ColoredPolygon(Polygon polygon, Color color) {
        this.polygon = polygon;
        this.color = color;
    }

    public Polygon getPolygon() {
        return polygon;
    }

    public Color getColor() {
        return color;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        ColoredPolygon that = (ColoredPolygon) o;
        return Objects.equals(polygon, that.polygon) &&
                color == that.color;
    }

    @Override
    public int hashCode() {
        return Objects.hash(polygon, color);
    }
}
