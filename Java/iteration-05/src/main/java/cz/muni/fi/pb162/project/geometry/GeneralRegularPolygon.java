package cz.muni.fi.pb162.project.geometry;

/**
 * @author Ondrej Kostik
 */
public class GeneralRegularPolygon implements RegularPolygon, Colored {
    private final Vertex2D center;
    private final int edgeNumber;
    private final double radius;
    private Color color = Color.BLACK;

    /**
     * Constructor of GeneralRegularPolygon
     * @param center is center of polygon
     * @param edgeNumber is number of edges of the polygon
     * @param radius is the radius of the polygon
     */
    public GeneralRegularPolygon(Vertex2D center, int edgeNumber, double radius) {
        this.center = center;
        this.edgeNumber = edgeNumber;
        this.radius = radius;
    }

    @Override
    public Color getColor() {
        return color;
    }

    @Override
    public void setColor(Color color) {
        this.color = color;
    }

    @Override
    public int getNumEdges() {
        return edgeNumber;
    }

    @Override
    public double getEdgeLength() {
        return 2*getRadius()*Math.sin(Math.PI/edgeNumber);
    }

    @Override
    public Vertex2D getVertex(int index) {
        double x = getCenter().getX() - getRadius()*Math.cos(index*2*Math.PI/edgeNumber);
        double y = getCenter().getY() - getRadius()*Math.sin(index*2*Math.PI/edgeNumber);
        return new Vertex2D(x, y);
    }

    @Override
    public double getHeight() {
        return getRadius()*2;
    }

    @Override
    public double getWidth() {
        return getHeight();
    }

    @Override
    public Vertex2D getCenter() {
        return center;
    }

    @Override
    public double getRadius() {
        return radius;
    }

    @Override
    public String toString() {
        return String.format("%s-gon: center=%s, radius=%s, color=%s",
                getNumEdges(),getCenter(),getRadius(),getColor());
    }
}
