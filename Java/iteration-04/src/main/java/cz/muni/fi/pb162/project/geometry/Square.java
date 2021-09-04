package cz.muni.fi.pb162.project.geometry;

/**
 * @author Ondrej Kostik
 */
public class Square implements Circular{
    private Vertex2D center;
    private double radius;

    /**
     * constructor, creates an instance of Square with parameters
     * @param center is a Vertex2D representing the center
     * @param diameter is a double representing the diameter
     */
    public Square(Vertex2D center, double diameter){
        this.center = center;
        this.radius = diameter/2;
    }

    /**
     * constructor, creates an instance of Square using a Circular
     * @param circle is a Circular
     */
    public Square(Circular circle){
        this(circle.getCenter(), 2 * circle.getRadius());
    }
    @Override
    public Vertex2D getCenter(){
        return center;
    }
    @Override
    public double getRadius(){
        return radius;
    }

    /**
     * @param index marks witch vertex to return
     * @return index-th Vertex of Square
     */
    public Vertex2D getVertex(int index){
        switch(index){
            case 0:
                return new Vertex2D(center.getX() - radius, center.getY());
            case 1:
                return new Vertex2D(center.getX(), center.getY() - radius);
            case 2:
                return new Vertex2D(center.getX() + radius, center.getY());
            case 3:
                return new Vertex2D(center.getX(), center.getY() + radius);
            default:
                return null;
        }
    }

    /**
     *
     * @return info about Square in a formatted output
     */
    @Override
    public String toString(){
        return String.format("Square: vertices=%s %s %s %s", getVertex(0), getVertex(1),
                getVertex(2), getVertex(3));
    }
}
