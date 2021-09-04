/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pb162.project.geometry;

/**
 *
 * @author Ondrej Kostik
 */
public final class Vertex2D {
    private final double x, y;
    /**
     * Vertex2D constructor
     * @param x stands for coordinate x
     * @param y stands for coordinate y
     */
    public Vertex2D(double x, double y){
        this.x = x;
        this.y = y;
    }
    
    public double getX(){
        return x;
    }
    public double getY(){
        return y;
    }
    /**
     * 
     * @return coordinates in a formatted output 
     */
    @Override
    public String toString(){
        return "[" + x + ", " + y + "]";
    }
    /**
     * Creates new Vertex2D with coordinates between original and given one
     * @param otherVertex a given Vertex2D vertex
     * @return new Vertex2D with new coordinates
     */
    public Vertex2D createMiddle(Vertex2D otherVertex){
        double newX = ((x + otherVertex.getX())/2);
        double newY = ((y + otherVertex.getY())/2);
        return new Vertex2D(newX, newY);
    }
    /**
     * returns Euclid's distance of our vertex and another one
     * @param vertex the "another one"
     * @return Euclid's distance in double
     */
    public double distance(Vertex2D vertex){
        if (vertex == null){
            return -1.0;
        }
        double a = Math.pow((vertex.x - this.x),2);
        double b = Math.pow((vertex.y - this.y),2);
        return Math.sqrt((a+b));    
    }
}