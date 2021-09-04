#include <vector>
#include <cmath>
#include <cassert>

/* A familiar class: add a 2-parameter constructor and x(), y()
 * accessors (the coordinates should be double-precision floating
 * point numbers). */

class point {
private:
    /** tohle není hezké, aby si ta třída skrytě držela další data, která podle
     ** zadání nemá potřebovat. Bylo by vhodnější si je držet zvlášť, případně
     ** mít další třídu, která si drží starý a nový point **/
    /** ve skutečnosti stačilo si v midpoints zapamatovat jen první bod, pro
     ** ostatní není třeba zachovávat staré i nové hodnoty. **/
    double x_coordinate, y_coordinate, x_new, y_new;
public:
    point(double x, double y) : x_coordinate(x), y_coordinate(y), x_new(x), y_new(y) {}

    double x() const {
        return x_coordinate;
    }

    double y() const {
        return y_coordinate;
    }

    void set_new(double x, double y) {
        x_new = x;
        y_new = y;
    }

    void refresh() {
        x_coordinate = x_new;
        y_coordinate = y_new;
    }
};


/* Consider a closed shape made of line segments. Replace each
 * segment A with one that starts at the midpoint of A and ends at
 * the midpoint of B, the segment that comes immediately after A.
 * The input is given as a sequence of points (each point shared by
 * two segments). The last segment goes from the last point to the
 * first point (closing the shape). */

void midpoints(std::vector<point> &pts) {
    assert(!pts.empty());
    double newX, newY;
    /* coordinates for first n-1 points */
    for (size_t i = 0; i < pts.size() - 1; i++) {
        newX = (pts[i].x() + pts[i + 1].x()) / 2;
        newY = (pts[i].y() + pts[i + 1].y()) / 2;
        pts[i].set_new(newX, newY);
    }
    /* coordinates for last point */
    /** duplikace kódu **/
    newX = (pts[pts.size() - 1].x() + pts[0].x()) / 2;
    newY = (pts[pts.size() - 1].y() + pts[0].y()) / 2;
    pts[pts.size() - 1].set_new(newX, newY);
    /* old coordinates are replaced by new ones */
    for (point &point : pts) {
        point.refresh();
    }
}

/* helper functions for floating-point almost-equality */

bool near( double a, double b )
{
    return std::fabs( a - b ) < 1e-8;
}

bool near( point a, point b )
{
    return near( a.x(), b.x() ) && near( a.y(), b.y() );
}

int main()
{
    using point_vec = std::vector< point >;

    point_vec s1{ { 0, 0 }, { 4, 0 }, { 4, 3 } };
    midpoints( s1 );

    assert( near( s1[ 0 ], point( 2, 0 ) ) );
    assert( near( s1[ 1 ], point( 4, 1.5 ) ) );
    assert( near( s1[ 2 ], point( 2, 1.5 ) ) );

    point_vec s2{ { 0, 0 }, { 0, 4 }, { 4, 4 }, { 4, 0 } };
    midpoints( s2 );

    assert( near( s2[ 0 ], point( 0, 2 ) ) );
    assert( near( s2[ 1 ], point( 2, 4 ) ) );
    assert( near( s2[ 2 ], point( 4, 2 ) ) );
    assert( near( s2[ 3 ], point( 2, 0 ) ) );
}
