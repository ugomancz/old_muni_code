package cz.muni.fi.pb162.project.geometry;

import java.util.Arrays;

/**
 * Class representing polygon using a list of vertices
 *
 * @author Ondrej Kostik
 */
public class ArrayPolygon extends SimplePolygon {

    private final Vertex2D[] vertices;

    /**
     * constructor first calls constructor of SimplePolygon, if it passes, it creates a new ArrayPolygon from
     * list of vertices
     *
     * @param vertices list of vertices
     */
    public ArrayPolygon(Vertex2D[] vertices) {
        super(vertices);
        this.vertices = Arrays.copyOf(vertices, vertices.length);
    }

    @Override
    public Vertex2D getVertex(int index) {
        if (index < 0) {
            throw new IllegalArgumentException("index is negative");
        }
        return vertices[index % getNumVertices()];
    }

    @Override
    public int getNumVertices() {
        return vertices.length;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        ArrayPolygon otherPol = (ArrayPolygon) o;
        if (getNumVertices() != otherPol.getNumVertices()) {
            return false;
        }
        for (int i = 0; i < getNumVertices(); i++) {
            if (!getVertex(i).equals(otherPol.getVertex(i))) {
                return false;
            }
        }
        return true;
    }

    @Override
    public int hashCode() {
        return Arrays.hashCode(vertices);
    }
}
