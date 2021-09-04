package cz.muni.fi.pb162.project.demo;
import cz.muni.fi.pb162.project.geometry.Triangle;
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
        Vertex2D verA = new Vertex2D(-100,0);
        Vertex2D verB = new Vertex2D(0,100);
        Vertex2D verC = new Vertex2D(100,-100);
        Triangle newtriangle = new Triangle(verA, verB, verC);
        System.out.println(newtriangle.toString());
    }
}
