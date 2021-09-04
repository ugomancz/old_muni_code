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
     * @return coordinates in a formatted output 
     */
    @Override
    public String toString(){
        return String.format("[%s, %s]", getX(), getY());
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
        double a = (vertex.x - this.x)*(vertex.x - this.x);
        double b = (vertex.y - this.y)*(vertex.y - this.y);
        return Math.sqrt((a+b));    
    }

    @Override
    public boolean equals(Object o) {
        if (this == o){
            return true;
        }
        if (o == null || getClass() != o.getClass()){
            return false;
        }
        Vertex2D vertex2D = (Vertex2D) o;
        return Double.compare(vertex2D.x, x) == 0 &&
                Double.compare(vertex2D.y, y) == 0;
    }

    @Override
    public int hashCode() {
        return Double.hashCode(x) << 8 | Double.hashCode(y);
    }
}