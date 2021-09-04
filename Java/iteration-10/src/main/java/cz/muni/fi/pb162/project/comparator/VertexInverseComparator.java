package cz.muni.fi.pb162.project.comparator;

import cz.muni.fi.pb162.project.geometry.Vertex2D;

import java.util.Comparator;

/**
 * @author Ondrej Kostik
 */
public class VertexInverseComparator implements Comparator<Vertex2D> {
    @Override
    public int compare(Vertex2D vertex1, Vertex2D vertex2) {
        return vertex2.compareTo(vertex1);
    }
}
