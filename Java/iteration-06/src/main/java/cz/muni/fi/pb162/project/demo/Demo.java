package cz.muni.fi.pb162.project.demo;
import cz.muni.fi.pb162.project.geometry.RegularOctagon;
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
        Vertex2D center = new Vertex2D(0,0);
        RegularOctagon newOctagon = new RegularOctagon(center, 1);
        System.out.println(newOctagon);
    }
}