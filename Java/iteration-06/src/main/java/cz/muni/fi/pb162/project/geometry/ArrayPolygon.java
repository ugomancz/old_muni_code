package cz.muni.fi.pb162.project.geometry;

import java.util.Arrays;

/**
 * Class representing polygon using a list of vertices
 * @author Ondrej Kostik
 */
public class ArrayPolygon extends SimplePolygon{

    private final Vertex2D[] vertices;

    /**
     * constructor of polygon defined by a list of vertices
     * @param vertices is a list of Vertex2D vertices defining the Polygon
     * @throws IllegalArgumentException if list is null or contains a null vertex
     */
    public ArrayPolygon(Vertex2D[] vertices) {
        if (vertices == null || Arrays.asList(vertices).contains(null)){
            throw new IllegalArgumentException("vertices or some vertex is null");
        }
        this.vertices = Arrays.copyOf(vertices, vertices.length);
    }

    @Override
    public Vertex2D getVertex(int index) {
        if (index < 0){
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
        if (this == o){
            return true;
        }
        if (o == null || getClass() != o.getClass()){
            return false;
        }
        ArrayPolygon otherPol = (ArrayPolygon) o;
        if (getNumVertices() != otherPol.getNumVertices()){
            return false;
        }
        for (int i = 0; i < getNumVertices(); i++){
            if (!getVertex(i).equals(otherPol.getVertex(i))){
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
