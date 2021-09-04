package cz.muni.fi.pb162.project.geometry;

import cz.muni.fi.pb162.project.utils.SimpleMath;

import java.util.Arrays;

/**
 * Abstract class to represent simple polygons
 *
 * @author Ondrej Kostik
 */
public abstract class SimplePolygon implements Polygon {
    /**
     * constructor only checks if vertices is null or contains a null Vertex2D
     * @param vertices is checked
     */
    public SimplePolygon(Vertex2D[] vertices){
        if (vertices == null || Arrays.asList(vertices).contains(null)) {
            throw new IllegalArgumentException("vertices or some vertex is null");
        }
    }

    @Override
    public double getWidth() {
        return SimpleMath.maxX(this) - SimpleMath.minX(this);
    }

    @Override
    public double getHeight() {
        return SimpleMath.maxY(this) - SimpleMath.minY(this);
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder("Polygon: vertices =");
        for (int i = 0; i < getNumVertices(); i++) {
            result.append(" ").append(getVertex(i));
        }
        return result.toString();
    }

    @Override
    public abstract int getNumVertices();
}
