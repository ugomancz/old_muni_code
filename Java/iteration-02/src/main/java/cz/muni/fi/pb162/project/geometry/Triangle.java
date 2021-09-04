/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.pb162.project.geometry;

/**
 * class that represents a triangle using 3 Vertex2D vertices
 * triangles can be split into 3 sub-triangles
 * @author Ondrej Kostik
 */
public class Triangle {
    private Vertex2D[] vert = new Vertex2D[3]; //vertices
    private Triangle[] subtriangles = new Triangle[3];
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
     * sets one vertex of a Triangle
     * @param index specifies which vertex
     * @param vertex new vertex
     */
    public void setVertex(int index, Vertex2D vertex){
        if (isInRange(index)){
            vert[index] = vertex;
        }
    }
    @Override
    public String toString(){
        String vertexA;
        String vertexB;
        String vertexC;
        vertexA = vert[0].toString();
        vertexB = vert[1].toString();
        vertexC = vert[2].toString();
        return "Triangle: vertices=" + vertexA.toString() + " " +
               vertexB.toString() + " " + vertexC.toString();
        
    }
    public boolean isDivided(){
        return subtriangles[0] != null
               && subtriangles[1] != null
               && subtriangles[2] != null;
    }
    /**
     * returns a specific sub-triangle of a Triangle
     * @param index specifies which sub-triangle
     * @return sub-triangle (Triangle) or null
     */
    public Triangle getSubTriangle(int index){
        if (isInRange(index)){
            return subtriangles[index];
        }
        return null;
    }
    /**
     * divides a Triangle into 3 sub-triangles
     * @return true if successful, false if Triangle is already divided
     */
    public boolean divide(){
        if (isDivided()){
            return false;
        }
        Triangle newA = new Triangle(vert[0], (vert[0].createMiddle(vert[1])),
                (vert[0].createMiddle(vert[2])));
        Triangle newB = new Triangle(vert[1], (vert[0].createMiddle(vert[1])),
                (vert[1].createMiddle(vert[2])));
        Triangle newC = new Triangle(vert[2], (vert[2].createMiddle(vert[1])),
                (vert[0].createMiddle(vert[2])));
        subtriangles[0] = newA;
        subtriangles[1] = newB;
        subtriangles[2] = newC;
        return true;
    }
}
