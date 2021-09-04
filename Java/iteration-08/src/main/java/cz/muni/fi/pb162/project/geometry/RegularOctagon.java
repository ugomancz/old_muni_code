package cz.muni.fi.pb162.project.geometry;

/**
 * RegularOctagon extends GeneralRegularPolygon for cases, where octagon specifically is used
 *
 * @author Ondrej Kostik
 */
public class RegularOctagon extends GeneralRegularPolygon {
    /**
     * Constructor of RegularOctagon, which is just a GeneralRegularPolygon with 8 edges
     *
     * @param center the center of octagon
     * @param radius the radius of octagon
     */
    public RegularOctagon(Vertex2D center, double radius) {
        super(center, 8, radius);
    }
}
