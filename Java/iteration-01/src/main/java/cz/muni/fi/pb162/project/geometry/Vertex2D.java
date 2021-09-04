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
public class Vertex2D {
    private double x, y;
    
    public double getX(){
        return x;
    }
    public double getY(){
        return y;
    }
    public void setX(double newX){
        x = newX;
    }
    public void setY(double newY){
        y = newY;
    }
    /**
     * 
     * @return coordinates in a formatted output 
     */
    public String getInfo(){
        return "[" + x + ", " + y + "]";
    }
    /**
     * 
     * @return the sum of coordinates 
     */
    public double sumCoordinates(){
        return x + y;
    }
    /**
     * changes vertex coordinates using new vertex's coordinates
     * @param vertex 
     */
    public void move(Vertex2D vertex){
        this.x += vertex.x;
        this.y += vertex.y;
        
    }
}
