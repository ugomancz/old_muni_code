/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package cz.muni.fi.pb162.project.geometry;

/**
 * class that represents a circle
 * circle has a center and a radius
 * @author Ondrej Kostik
 */
public class Circle implements Measurable, Circular{
    private final Vertex2D center;
    private final double radius;
    /**
     * constructor
     * @param center center of a circle
     * @param radius radius of a circle
     */
    public Circle(Vertex2D center, double radius){
        this.center = center;
        this.radius = radius;
    }
    /**
     * constructor
     * creates a basic circle with center at [0,0] and radius of 1
     */
    public Circle(){
        this(new Vertex2D(0,0),1);
    }

    @Override
    public double getHeight() {
        return 2*radius;
    }

    @Override
    public double getWidth() {
        return getHeight();
    }
    @Override
    public double getRadius(){
        return radius;
    }
    @Override
    public Vertex2D getCenter(){
        return center;
    }
    /**
     * 
     * @return info about Circle in a formatted output
     */
    @Override
    public String toString(){
        return "Circle: center=" + center.toString() + ", radius=" + radius;
    }
}
