package cz.muni.fi.pb162.project.utils;

import cz.muni.fi.pb162.project.geometry.Triangle;

/**
 * class to find out smallest/largest X/Y coordinates of Triangle
 * @author Ondrej Kostik
 */
public class SimpleMath {
    /**
     * method to return smallest X coordinate of Triangle's vertices
     * @param triangle is an instance of class Triangle
     * @return smallest X coordinate of Triangle
     */
    public static double minX(Triangle triangle){
        double a = triangle.getVertex(0).getX();
        double b = triangle.getVertex(1).getX();
        double c = triangle.getVertex(2).getX();
        return Math.min(a, Math.min(b,c));
    }

    /**
     * method to return smallest Y coordinate of Triangle's vertices
     * @param triangle is an instance of class Triangle
     * @return smallest Y coordinate of Triangle
     */
    public static double minY(Triangle triangle){
        double a = triangle.getVertex(0).getY();
        double b = triangle.getVertex(1).getY();
        double c = triangle.getVertex(2).getY();
        return Math.min(a, Math.min(b,c));
    }
    /**
     * method to return biggest X coordinate of Triangle's vertices
     * @param triangle is an instance of class Triangle
     * @return biggest X coordinate of Triangle
     */
    public static double maxX(Triangle triangle){
        double a = triangle.getVertex(0).getX();
        double b = triangle.getVertex(1).getX();
        double c = triangle.getVertex(2).getX();
        return Math.max(a, Math.max(b,c));
    }
    /**
     * method to return biggest Y coordinate of Triangle's vertices
     * @param triangle is an instance of class Triangle
     * @return biggest Y coordinate of Triangle
     */
    public static double maxY(Triangle triangle){
        double a = triangle.getVertex(0).getY();
        double b = triangle.getVertex(1).getY();
        double c = triangle.getVertex(2).getY();
        return Math.max(a, Math.max(b,c));
    }
}
