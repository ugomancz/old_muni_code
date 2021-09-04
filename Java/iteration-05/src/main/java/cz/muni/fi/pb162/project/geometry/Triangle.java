/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pb162.project.geometry;

import cz.muni.fi.pb162.project.utils.SimpleMath;
/**
 * class that represents a triangle using 3 Vertex2D vertices
 * triangles can be split into 3 sub-triangles
 * @author Ondrej Kostik
 */
public class Triangle implements Measurable{
    private final Vertex2D[] vert = new Vertex2D[3]; //vertices
    private final Triangle[] subT = new Triangle[3];
    private static final double MAX_ERROR = 0.001;
    /**
     * constructor of Triangle
     * @param a is a Vertex2D with coordinates of vertex A
     * @param b is a Vertex2D with coordinates of vertex B
     * @param c is a Vertex2D with coordinates of vertex C
     */
    public Triangle(Vertex2D a, Vertex2D b, Vertex2D c){
        vert[0] = a;
        vert[1] = b;
        vert[2] = c;
    }

    /**
     * constructor of Sierpinski triangle
     * @param a is a Vertex2D with coordinates of vertex A
     * @param b is a Vertex2D with coordinates of vertex B
     * @param c is a Vertex2D with coordinates of vertex C
     * @param depth specifies the depth of recursion of Sierpinski triangle
     */
    public Triangle(Vertex2D a, Vertex2D b, Vertex2D c, int depth){
        this(a,b,c);
        divide(depth);
    }

    @Override
    public double getWidth(){
        return (SimpleMath.maxX(this) - SimpleMath.minX(this));
    }

    @Override
    public double getHeight(){
        return (SimpleMath.maxY(this) - SimpleMath.minY(this));
    }

    /**
     * checks if index is in range [0,2]
     * @param index the number checked
     * @return false/true
     */
    public boolean isInRange(int index){
        if (index < 0){
            return false;
        }
        if (index > 2){
            return false;
        }
        return true;
    }
    /**
     * returns one vertex of a Triangle
     * @param index specifies which vertex
     * @return the vertex
     */
    public Vertex2D getVertex(int index){
        if (isInRange(index)){
            return vert[index];
        }
        return null;
    }

    /**
     * @return info about triangle in a formatted output
     */
    @Override
    public String toString(){
        String vertexA;
        String vertexB;
        String vertexC;
        vertexA = vert[0].toString();
        vertexB = vert[1].toString();
        vertexC = vert[2].toString();
        return String.format("Triangle: vertices=%s %s %s", vertexA.toString(),
               vertexB.toString(), vertexC.toString());
        
    }

    /**
     * checks if Triangle is already divided
     * @return True or False
     */
    public boolean isDivided(){
        return subT[0] != null
               && subT[1] != null
               && subT[2] != null;
    }
    /**
     * returns a specific sub-triangle of a Triangle
     * @param index specifies which sub-triangle
     * @return sub-triangle (Triangle) or null
     */
    public Triangle getSubTriangle(int index){
        if (isInRange(index)){
            return subT[index];
        }
        return null;
    }
    /**
     * decides if triangle is equilateral
     * @return true or false
     */
    public boolean isEquilateral(){
        double lengthA = vert[0].distance(vert[1]);
        double lengthB = vert[1].distance(vert[2]);
        double lengthC = vert[0].distance(vert[2]);
        if ((Math.abs(lengthA - lengthB) < MAX_ERROR) &&
            (Math.abs(lengthB - lengthC) < MAX_ERROR) &&
            (Math.abs(lengthC - lengthA) < MAX_ERROR)){
            return true;
        }
        return false;
    }
    /**
     * divides a Triangle into 3 sub-triangles
     * @return true if successful, false if Triangle is already divided
     */
    public boolean divide(){
        if (isDivided()){
            return false;
        }
        subT[0] = new Triangle(vert[0], (vert[0].createMiddle(vert[1])),
                (vert[0].createMiddle(vert[2])));
        subT[1] = new Triangle(vert[1], (vert[0].createMiddle(vert[1])),
                (vert[1].createMiddle(vert[2])));
        subT[2] = new Triangle(vert[2], (vert[2].createMiddle(vert[1])),
                (vert[0].createMiddle(vert[2])));
        return true;
    }
    /**
     * creates a Sierpinski triangle
     * @param depth the depth of recursion
     */
    public void divide(int depth){
        if (depth == 0){
            return;
        }
        divide();
        subT[0].divide(depth-1);
        subT[1].divide(depth-1);
        subT[2].divide(depth-1);
    }
}
