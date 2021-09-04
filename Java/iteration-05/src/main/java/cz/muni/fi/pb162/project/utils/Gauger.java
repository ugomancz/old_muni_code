package cz.muni.fi.pb162.project.utils;

import cz.muni.fi.pb162.project.geometry.Measurable;
import cz.muni.fi.pb162.project.geometry.Triangle;

/**
 * Class to return info about Measurable items in a formatted output
 * @author Ondrej Kostik
 */
public class Gauger {
    /**
     * prints info about Measurable item in a formatted output
     * @param someItem is a Measurable
     */
    public static void printMeasurement(Measurable someItem){
        System.out.printf("Width: %s%nHeight: %s%n", someItem.getWidth(), someItem.getHeight());
    }

    /**
     * prints info about triangle in a formatted output, then
     * prints info about same triangle as a Measurable item
     * @param someTriangle is an instance of class Triangle
     */
    public static void printMeasurement(Triangle someTriangle){
        System.out.println(someTriangle.toString());
        printMeasurement((Measurable) someTriangle);
    }
}
