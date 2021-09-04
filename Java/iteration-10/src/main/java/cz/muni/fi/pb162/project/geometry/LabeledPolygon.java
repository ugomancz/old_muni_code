package cz.muni.fi.pb162.project.geometry;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
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
public final class LabeledPolygon extends SimplePolygon implements Polygon, Sortable, Labelable, PolygonWritable {
    private static final Gson GSON_WRITER = new GsonBuilder().setPrettyPrinting().create();
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

    @Override
    public void write(OutputStream os) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os));
        try {
            for (Map.Entry<String, Vertex2D> entry : vertices.entrySet()) {
                Vertex2D vertex = entry.getValue();
                writer.write(String.format("%s %s %s", vertex.getX(), vertex.getY(), entry.getKey()));
                writer.newLine();
            }
        } finally {
            writer.flush();
        }
    }

    @Override
    public void write(File file) throws IOException {
        try (FileOutputStream out = new FileOutputStream(file)) {
            write(out);
        }
    }

    /**
     * writes a map in json format to output stream
     *
     * @param out Stream
     * @throws IOException from BufferedWriter
     */
    public void writeJson(OutputStream out) throws IOException {
        String json = GSON_WRITER.toJson(vertices);
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(out));
        try {
            writer.write(json);
        } finally {
            writer.flush();
        }
    }

    /**
     * @author Ondrej Kostik
     */
    public static class Builder implements Buildable<LabeledPolygon>, PolygonReadable {
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

        @Override
        public Builder read(InputStream is) throws IOException {
            BufferedReader reader = new BufferedReader(new InputStreamReader(is));
            String line = reader.readLine();
            Map<String, Vertex2D> tmpVertices = new TreeMap<>();
            while (line != null) {
                addLineToPolygon(line, tmpVertices);
                line = reader.readLine();
            }
            vertices.putAll(tmpVertices);
            return this;
        }

        private void addLineToPolygon(String line, Map<String, Vertex2D> tmpVertices) throws IOException {
            String[] parsedLine = line.split(" ", 3);
            if (parsedLine.length != 3) {
                throw new IOException("Invalid line format");
            }
            try {
                Double x = Double.parseDouble(parsedLine[0]);
                Double y = Double.parseDouble(parsedLine[1]);
                tmpVertices.put(parsedLine[2], new Vertex2D(x, y));
            } catch (NumberFormatException | NullPointerException ex) {
                throw new IOException("Invalid number format", ex);
            }
        }

        @Override
        public Builder read(File file) throws IOException {
            try (InputStream in = new FileInputStream(file)) {
                read(in);
            }
            return this;
        }
    }
}