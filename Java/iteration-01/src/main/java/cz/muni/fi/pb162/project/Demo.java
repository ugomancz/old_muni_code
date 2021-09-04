package cz.muni.fi.pb162.project;
import cz.muni.fi.pb162.project.geometry.Vertex2D;

/**
 * Class for running main method.
 * Simple demonstration of a class used during the first seminar.
 *
 * @author Ondrej Kostik
 */
public class Demo {

    /**
     * Runs the code.
     *
     * @param args command line arguments, will be ignored
     */
    public static void main(String[] args) {

        Vertex2D vertexA, vertexB;
        vertexA = new Vertex2D();
        vertexB = new Vertex2D();
        vertexA.setX(2.0);
        vertexA.setY(3.0);
        vertexB.setX(1.0);
        vertexB.setY(1.0);
        vertexA.move(vertexB);
        System.out.println(vertexA.getInfo());
        System.out.println(vertexB.getInfo());

    }
}
