package cz.muni.fi.pb162.project.utils;

import cz.muni.fi.pb162.project.geometry.Polygon;

/**
 * class to find out smallest/largest X/Y coordinates of Polygon
 *
 * @author Ondrej Kostik
 */
public class SimpleMath {
    /**
     * method to return smallest X coordinate of Polygon's vertices
     *
     * @param polygon is an instance of Polygon
     * @return smallest X coordinate of Polygon
     */
    public static double minX(Polygon polygon) {
        double minX = polygon.getVertex(0).getX();
        for (int i = 0; i < polygon.getNumVertices(); i++) {
            if (polygon.getVertex(i).getX() < minX) {
                minX = polygon.getVertex(i).getX();
            }
        }
        return minX;
    }

    /**
     * method to return smallest Y coordinate of Polygon's vertices
     *
     * @param polygon is an instance of Polygon
     * @return smallest Y coordinate of Polygon
     */
    public static double minY(Polygon polygon) {
        double minY = polygon.getVertex(0).getY();
        for (int i = 0; i < polygon.getNumVertices(); i++) {
            if (polygon.getVertex(i).getY() < minY) {
                minY = polygon.getVertex(i).getY();
            }
        }
        return minY;
    }

    /**
     * method to return biggest X coordinate of Polygon's vertices
     *
     * @param polygon is an instance of Polygon
     * @return biggest X coordinate of Polygon
     */
    public static double maxX(Polygon polygon) {
        double maxX = polygon.getVertex(0).getX();
        for (int i = 0; i < polygon.getNumVertices(); i++) {
            if (polygon.getVertex(i).getX() > maxX) {
                maxX = polygon.getVertex(i).getX();
            }
        }
        return maxX;
    }

    /**
     * method to return biggest Y coordinate of Polygon's vertices
     *
     * @param polygon is an instance of Polygon
     * @return biggest Y coordinate of Polygon
     */
    public static double maxY(Polygon polygon) {
        double maxY = polygon.getVertex(0).getY();
        for (int i = 0; i < polygon.getNumVertices(); i++) {
            if (polygon.getVertex(i).getY() > maxY) {
                maxY = polygon.getVertex(i).getY();
            }
        }
        return maxY;
    }
}
