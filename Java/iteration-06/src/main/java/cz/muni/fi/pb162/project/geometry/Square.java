package cz.muni.fi.pb162.project.geometry;

/**
 * @author Ondrej Kostik
 */
public class Square extends GeneralRegularPolygon implements Circular{

    /**
     * Constructor, creates an instance of Square with parameters
     * Gives the square 4 edges, because it's a square
     * @param center is a Vertex2D representing the center
     * @param diameter is a double representing the diameter
     */
    public Square(Vertex2D center, double diameter){
        super(center, 4, diameter/2);
    }

    /**
     * constructor, creates an instance of Square using a Circular
     * @param circle is a Circular
     */
    public Square(Circular circle){
        this(circle.getCenter(), 2 * circle.getRadius());
    }

    /**
     * @return info about Square in a formatted output
     */
    @Override
    public String toString(){
        return String.format("Square: vertices=%s %s %s %s", getVertex(0), getVertex(1),
                getVertex(2), getVertex(3));
    }
}
