/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package cz.muni.fi.pb162.project.geometry;

/**
 * class that represents almost perfect circle using GeneralRegularPolygon
 * with around 2.15 billion edges (Integer.MAX_VALUE)
 *
 * @author Ondrej Kostik
 */
public class Circle extends GeneralRegularPolygon implements Measurable, Circular {
    /**
     * Constructor of a circle, creates a GeneralRegularPolygon with maximum number of edges,
     * not literally a circle, but as close as a GeneralRegularPolygon can get.
     * Has implicitly red color.
     *
     * @param center is the center of circle
     * @param radius is the radius of circle
     */
    public Circle(Vertex2D center, double radius) {
        super(center, Integer.MAX_VALUE, radius);
        setColor(Color.RED);
    }

    /**
     * creates a basic Circle with center at [0,0] and radius of 1
     */
    public Circle() {
        this(new Vertex2D(0, 0), 1);
    }

    @Override
    public double getEdgeLength() {
        return 0.0;
    }

    /**
     * @return info about Circle in a formatted output
     */
    @Override
    public String toString() {
        return String.format("Circle: center=%s, radius=%s", getCenter(), getRadius());
    }
}
