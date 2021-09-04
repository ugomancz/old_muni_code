package cz.muni.fi.pb162.project.geometry;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

/**
 * @author Ondrej Kostik
 */
public class CollectionPolygon extends SimplePolygon {
    private final List<Vertex2D> vertices;

    /**
     * constructor of CollectionPolygon using an array
     *
     * @param vertices is an array of Vertex2D vertices
     */
    public CollectionPolygon(Vertex2D[] vertices) {
        super(vertices);
        this.vertices = new ArrayList<>(Arrays.asList(vertices));
    }

    /**
     * Constructor of CollectionPolygon using a List
     *
     * @param vertices is a List of Vertex2D vertices
     */
    public CollectionPolygon(List<Vertex2D> vertices) {
        this(vertices.toArray(new Vertex2D[0]));


    }

    @Override
    public Vertex2D getVertex(int index) {
        if (index < 0) {
            throw new IllegalArgumentException("index < 0");
        }
        return vertices.get(index % getNumVertices());
    }

    @Override
    public int getNumVertices() {
        return vertices.size();
    }

    /**
     * @return CollectionPolygon without leftmost vertices
     */
    public CollectionPolygon withoutLeftmostVertices() {
        if (vertices.isEmpty()) {
            throw new IllegalArgumentException("empty");
        }
        Vertex2D leftMost = Collections.min(vertices, Comparator.comparingDouble(Vertex2D::getX));
        List<Vertex2D> newVertices = vertices.stream().filter((Vertex2D x) ->
                (x.getX() > leftMost.getX())).collect(Collectors.toList());
        return new CollectionPolygon(newVertices);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        CollectionPolygon that = (CollectionPolygon) o;
        return Objects.equals(vertices, that.vertices);
    }

    @Override
    public int hashCode() {
        return Objects.hash(vertices);
    }
}
