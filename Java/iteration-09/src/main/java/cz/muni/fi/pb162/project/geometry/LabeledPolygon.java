package cz.muni.fi.pb162.project.geometry;

import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.Map;
import java.util.SortedMap;
import java.util.SortedSet;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.stream.Collectors;

/**
 * @author Ondrej Kostik
 */
public final class LabeledPolygon extends SimplePolygon implements Polygon, Sortable, Labelable {
    private SortedMap<String, Vertex2D> vertices;

    /**
     * constructor calls upon SimplePolygon constructor, if ok, saves argument map as own map
     *
     * @param vertices SortedMap of vertices and their labels
     */
    private LabeledPolygon(SortedMap<String, Vertex2D> vertices) {
        super(vertices.values().toArray(new Vertex2D[vertices.size()]));
        this.vertices = new TreeMap<>(vertices);
    }

    @Override
    public Vertex2D getVertex(int index) {
        if (index < 0) {
            throw new IllegalArgumentException("index < 0");
        }
        String label = vertices.keySet().toArray(new String[0])[index % getNumVertices()];
        return vertices.get(label);
    }

    @Override
    public int getNumVertices() {
        return vertices.keySet().size();
    }

    @Override
    public Vertex2D getVertex(String label) {
        if (!vertices.containsKey(label)) {
            throw new IllegalArgumentException(String.format("No vertex with %s label.", label));
        }
        return vertices.get(label);
    }

    @Override
    public Collection<String> getLabels() {
        return Collections.unmodifiableSet(vertices.keySet());
    }

    @Override
    public Collection<String> getLabels(Vertex2D vertex) {
        return vertices.entrySet().stream()
                .filter((e) -> e.getValue().equals(vertex))
                .map(Map.Entry::getKey)
                .collect(Collectors.toList());
    }

    @Override
    public Collection<Vertex2D> getSortedVertices() {
        return new TreeSet<>(vertices.values());
    }

    @Override
    public Collection<Vertex2D> getSortedVertices(Comparator<Vertex2D> comparator) {
        SortedSet<Vertex2D> newVertices = new TreeSet<>(comparator);
        newVertices.addAll(vertices.values());
        return newVertices;
    }

    /**
     * @return set of identical vertices saved with different key
     */
    public Collection<Vertex2D> duplicateVertices() {
        return vertices.entrySet().stream()
                .filter(e -> Collections.frequency(vertices.values(), e.getValue()) > 1)
                .map(Map.Entry::getValue).distinct()
                .collect(Collectors.toList());
    }

    /**
     * @author Ondrej Kostik
     */
    public static class Builder implements Buildable<LabeledPolygon> {
        private final SortedMap<String, Vertex2D> vertices = new TreeMap<>();

        @Override
        public LabeledPolygon build() {
            return new LabeledPolygon(vertices);
        }

        /**
         * adds a vertex to set, if there is one already, it gets replaced
         *
         * @param label  is key
         * @param vertex is value (Vertex2D)
         * @return instance of Builder
         */
        public Builder addVertex(String label, Vertex2D vertex) {
            if (label == null || vertex == null) {
                throw new IllegalArgumentException("label or vertex is null");
            }
            vertices.put(label, vertex);
            return this;
        }
    }
}