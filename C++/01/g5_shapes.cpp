/* Another exercise about objects, this time about their
 * composition. We will write 2 classes: ‹point› and ‹rectangle›.
 * Points have 2 coordinates (⟦x⟧ and ⟦y⟧) and rectangles are
 * defined by 2 points (their opposing corners). */

#include <cmath>
#include <cassert>

/* Points are constructed from two doubles: the ⟦x⟧ and ⟦y⟧
 * coordinates, and they have ‹x()› and ‹y()› methods which return
 * doubles. */

class point {
private:
    const double x_coordinate, y_coordinate;
public:
    point(const double x, const double y) : x_coordinate(x), y_coordinate(y) {}

    double x() const {
        return x_coordinate;
    }

    double y() const {
        return y_coordinate;
    }
};

/* A function to compute euclidean distance between two points.
 * Writing it is a part of the exercise, but it will be also useful
 * when implementing the ‹diagonal› method in ‹rectangle›. */

double distance(point a, point b) {
    return std::sqrt(std::pow(b.x() - a.x(), 2) + std::pow(b.y() - a.y(), 2));
}

/* Rectangles are constructed from a pair of points (bottom left and
 * upper right corner) and provide methods: ‹width›, ‹height› and
 * ‹diagonal› which all return a ‹double›, and a method ‹center›
 * which returns a ‹point›. */

class rectangle {
private:
    const point bottom_left, upper_right;
public:
    rectangle(const point &bottomLeft, const point &upperRight) : bottom_left(bottomLeft), upper_right(upperRight) {}

    double width() const {
        return (upper_right.x() - bottom_left.x());
    }

    double height() const {
        return (upper_right.y() - bottom_left.y());
    }

    double diagonal() const {
        return distance(bottom_left, upper_right);
    }

    point center() const {
        return point{bottom_left.x() + width()/2,bottom_left.y() + height()/2};
    }
};

int main()
{
    /* check that distance works okay */
    const point a( 0, 0 ), b( 0, 1 ), c( 4, 4 ), d( 4, 5 );
    assert( distance( a, b ) == 1 );
    assert( std::round( distance( b, c ) ) == 5 );

    const rectangle r( b, c ), s( b, d );
    assert( r.width() == 4 );
    assert( r.height() == 3 );
    assert( std::round( r.diagonal() ) == 5 );

    assert( std::round( s.center().x() ) == 2 );
    assert( std::round( s.center().y() ) == 3 );
}
