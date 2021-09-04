package cz.muni.fi.pb162.project.geometry;

/**
 * @author Ondrej Kostik
 * class represents a drawing of a "snowman" using Circular
 */
public class Snowman {
    private static final double DEFAULT_RATIO = 0.8;
    private static final int NUMBER_OF_BALLS = 4;
    private Circular[] balls = new Circular[4];

    /**
     * constructor, creates a Snowman instance and saves in an array of Circulars
     * @param circle is the "lowest" ball of snowman
     * @param factor by which are other balls smaller
     */
    public Snowman(Circular circle, double factor){
        balls[0] = circle;
        balls[1] = factoredCircular(circle, factor);
        balls[2] = factoredCircular(balls[1], factor);
        balls[3] = factoredCircular(balls[2], factor);
    }

    /**
     * takes a Circular and returns a new Circular smaller by factor
     * @param circle the original circle
     * @param factor the factor
     * @return new Circular
     */
    private Circular factoredCircular(Circular circle, double factor){
        if (!(factor <= 1 && factor >0)){
            factor = DEFAULT_RATIO;
        }
        Vertex2D newCenter = new Vertex2D(circle.getCenter().getX(), circle.getCenter().getY() + circle.getRadius() +
                circle.getRadius()*factor);
        return (Circular) new Circle(newCenter, circle.getRadius()*factor);
    }

    /**
     *
     * @return a copy of array of balls that make up the "snowman"
     */
    public Circular[] getBalls(){
        Circular[] newBalls = new Circular[NUMBER_OF_BALLS];
        System.arraycopy(balls, 0, newBalls,0, NUMBER_OF_BALLS);
        return newBalls;
    }
}