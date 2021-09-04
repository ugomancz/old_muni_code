/* In this task, you will implement a few bits of basic linear
 * algebra on top of an arbitrary scalar field, given as a template
 * parameter. Your solution will be tested with the ‹complex› and
 * ‹real› classes from task set 2 (which you will submit along with
 * this solution, see below) and also using a reference
 * implementation of those classes.
 *
 * Implement these 2 data types: ‹vector› and ‹matrix› (please try
 * to avoid confusing ‹vector› with ‹std::vector›). In addition to
 * methods prescribed below, implement the following operators:
 *
 *  • vector addition and subtraction (operators ‹+› and ‹-›),
 *  • multiplication of a vector by a scalar (from both sides, ‹*›),
 *  • dot product of two vectors (operator ‹*›),
 *  • matrix addition (operator ‹+›),
 *  • multiplication of a vector by a matrix (again ‹*›, both sides),
 *  • multiplication of compatible matrices (again ‹*›),
 *  • multiplication of matrix by a scalar (‹*› once more),
 *  • equality on both vectors and matrices,
 *  • indexing of vectors to get or change their entries,
 *  • indexing of matrices to get or change their rows. */

/* Note: you need to submit a working version of the ‘complex’ task
 * from the task set 2 along with this one, including the solution
 * of ‘natural’ if applicable (though ‘natural’ is not directly
 * required, so only include it if your solution of task ‘complex’
 * needs it). Add a copy of the relevant files to this directory
 * before you submit.
 *
 * Only the exact arithmetic part of ‘complex’ is required: the
 * approximation part (‹abs›, ‹arg›, ‹exp›, ‹log1p›) can be left
 * out. You should also add this (explicit) constructor if you
 * don't have one: ‹complex( int v )›. */

// extra files: complex.hpp complex.cpp natural.hpp natural.cpp

#include "complex.hpp" /* required! */
#include <vector>

template< typename scalar_ >
struct vector
{
    using scalar = scalar_;

    explicit vector( int dimension ); /* construct a zero vector */
    explicit vector( const std::vector< scalar > & );

    int dim() const; /* return the dimension */
};

template< typename scalar_ >
struct matrix
{
    using scalar = scalar_;
    using vector = ::vector< scalar >;

    matrix( int rows, int columns ); /* construct a zero matrix */
    explicit matrix( const std::vector< vector > &rows );

    /* The following two methods give the user direct access to the
     * values stored in the matrix (through column and row vectors).
     * The ‹n› is a 0-based index, starting from top (row) or left
     * (column). You may return ‹const› references if appropriate. */

    vector row( int n ) const;
    vector col( int n ) const;

    int cols() const;
    int rows() const;

    /* Compute basic properties of matrices. */

    int rank() const;
    scalar det() const;       /* determinant */
    matrix inv() const;       /* inverse matrix */
    matrix transpose() const; /* transpose matrix */

    /* Performs in-place Gaussian elimination: after the call,
     * the matrix should be in a reduced row echelon form. */

    void gauss();
};

/* Note: the behaviour is undefined if the ‹vector› instances passed
 * to a ‹matrix› constructor are not all of the same dimension and
 * when ‹det› or ‹inv› are called on a non-square matrix or ‹inv› on
 * a singular matrix. Likewise, operations on dimensionally
 * mismatched arguments are undefined. All dimensions must be
 * positive. */
