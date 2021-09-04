package cz.muni.fi.pb162.project.geometry;

import cz.muni.fi.pb162.project.exception.EmptyDrawableException;
import cz.muni.fi.pb162.project.exception.MissingVerticesException;
import cz.muni.fi.pb162.project.exception.TransparentColorException;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * @author Ondrej Kostik
 */
public class Paper implements Drawable, PolygonFactory {
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
    public void drawPolygon(Polygon polygon) throws TransparentColorException {
        if (pen == Color.WHITE) {
            throw new TransparentColorException("drawing " + pen.toString());
        }
        canvas.add(new ColoredPolygon(polygon, pen));
    }

    @Override
    public void erasePolygon(ColoredPolygon polygon) {
        canvas.remove(polygon);
    }

    @Override
    public void eraseAll() throws EmptyDrawableException {
        if (canvas.isEmpty()) {
            throw new EmptyDrawableException("Canvas is empty");
        }
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

    @Override
    public Polygon tryToCreatePolygon(List<Vertex2D> vertices) throws MissingVerticesException {
        if (vertices == null) {
            throw new NullPointerException("vertices is null");
        }
        List<Vertex2D> newVertices = new ArrayList<>(vertices);
        try {
            return new CollectionPolygon(newVertices);
        } catch (IllegalArgumentException e) {
            List<Vertex2D> correctedVertices = newVertices.stream()
                    .filter(vertex2D -> vertex2D != null)
                    .collect(Collectors.toList());
            return new CollectionPolygon(correctedVertices);
        }
    }

    @Override
    public void tryToDrawPolygons(List<List<Vertex2D>> collectionPolygons) throws EmptyDrawableException {
        int drawn = 0;
        Throwable last = null;
        for (List<Vertex2D> polygonVerts : collectionPolygons) {
            Polygon polygon = null;
            try {
                polygon = tryToCreatePolygon(polygonVerts);
                drawPolygon(polygon);
                drawn++;
            } catch (TransparentColorException ce) {
                changeColor(Color.BLACK);
                last = ce;
            } catch (MissingVerticesException | NullPointerException ex) {
                last = ex;
            }
        }
        if (drawn == 0) {
            throw new EmptyDrawableException("no polygon drawn", last);
        }
    }

    /**
     * Returns all polygons with given color
     *
     * @param color is a Color enum
     * @return a Collection of polygons
     */
    public Collection<Polygon> getPolygonsWithColor(Color color) {
        return canvas.stream()
                .filter(poly -> poly.getColor() == color)
                .map(ColoredPolygon::getPolygon)
                .collect(Collectors.toList());
    }
}
