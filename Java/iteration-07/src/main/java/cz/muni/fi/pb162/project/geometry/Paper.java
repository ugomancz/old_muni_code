package cz.muni.fi.pb162.project.geometry;

import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

/**
 * @author Ondrej Kostik
 */
public class Paper implements Drawable {
    private Set<ColoredPolygon> canvas;
    private Color pen;

    /**
     * constructor, creates a blank "paper" with pen colored black
     */
    public Paper() {
        canvas = new HashSet<>();
        pen = Color.BLACK;
    }

    /**
     * constructor, takes a copy of other Drawable's ColoredPolygon collection
     *
     * @param paper is a Drawable from which we copy
     */
    public Paper(Drawable paper) {
        this.canvas = new HashSet<>(paper.getAllDrawnPolygons());
    }

    @Override
    public void changeColor(Color color) {
        this.pen = color;
    }

    @Override
    public void drawPolygon(Polygon polygon) {
        if (pen != Color.WHITE) {
            canvas.add(new ColoredPolygon(polygon, pen));
        }
    }

    @Override
    public void erasePolygon(ColoredPolygon polygon) {
        canvas.remove(polygon);
    }

    @Override
    public void eraseAll() {
        canvas.clear();
    }

    @Override
    public Collection<ColoredPolygon> getAllDrawnPolygons() {
        return Collections.unmodifiableSet(canvas);
    }

    @Override
    public int uniqueVerticesAmount() {
        Set<Vertex2D> verts = new HashSet<>();
        for (ColoredPolygon tmpPoly : canvas) {
            Polygon poly = tmpPoly.getPolygon();
            for (int i = 0; i < poly.getNumVertices(); i++) {
                verts.add(poly.getVertex(i));
            }
        }
        return verts.size();
    }
}
