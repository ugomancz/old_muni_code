package cz.muni.fi.pb162.project.demo;

import cz.muni.fi.pb162.project.geometry.LabeledPolygon;
import cz.muni.fi.pb162.project.geometry.Vertex2D;

import java.io.File;
import java.io.IOException;

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
     * @throws IOException if LabeledPolygon cannot be built
     */
    public static void main(String[] args) throws IOException {
        new LabeledPolygon.Builder().read(new File("polygon-ok.txt"))
                .addVertex("vrchol x", new Vertex2D(123, 456))
                .build().writeJson(System.out);
        System.out.println("Hello World!");
    }
}