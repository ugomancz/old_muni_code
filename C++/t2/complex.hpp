/* In this exercise, you will implement exact (arbitrary-precision)
 * real and complex numbers. You can use the ‹natural› task as a
 * base, if you wish. Both real and complex numbers should provide
 * the standard array of arithmetic operators: addition,
 * subtraction, unary minus, multiplication and division. Real
 * numbers should have all relational operators and complex numbers
 * should have equality (‹==› and ‹!=›).
 *
 * Note: keep your representation normalised – complexity of
 * operations should only depend on the represented number, not on
 * the way it was obtained. */

// extra files: natural.hpp natural.cpp

class real
{
public:
    explicit real( int v = 0 );
    real abs() const;
    real reciprocal() const;
    real power( int n ) const;
};

class complex
{
    static inline const real epsilon = real( 1 ) / real( 1000000 );
public:
    explicit complex( real real_part = real( 0 ),
                      real imaginary_part = real( 0 ) );

    real real_part();
    real imaginary_part();

    complex reciprocal() const;
    complex power( int n ) const;

    /* Compute the:
     *
     *   • exponential function ⟦exp(z)⟧,
     *   • the natural logarithm ⟦ln(1 + z)⟧,
     *
     * where ⟦z⟧ is ‹this›. Use the respective Taylor expansions at
     * 0 (i.e. the Maclaurin series). The number of terms to use is
     * given by ‹terms›. */

    complex exp( int terms ) const;
    complex log1p( int terms ) const;

    /* Compute the absolute value of the given complex number to the
     * given precision (the argument ‹prec› gives the upper bound on
     * the admissible approximation error). You may find the
     * ‹newton› demo from week 2 helpful to compute ‹abs›. Don't
     * forget to find a suitable starting point for the
     * approximation, otherwise convergence will be very slow. */

    real abs( real prec = epsilon ) const;

    /* To compute the argument, you will need the inverse tangent
     * (‹atan›), which can be approximated using its Maclaurin
     * series in the closed interval ⟦⟨-1, 1⟩⟧. There is only one
     * problem: the convergence near ⟦±1⟧ is very slow. Hence, you
     * want to use a different series here (discovered by Euler):
     *
     * ⟦ ∑ 2²ⁿ(n!)²x²ⁿ⁺¹ / (2n + 1)!(1 + x²)ⁿ⁺¹ ⟧
     *
     * Though this one will eventually converge everywhere, it is
     * particularly good in the same ⟦⟨-1, 1⟩⟧ interval. In this
     * interval, it can be truncated at the first term less than
     * half the required precision.
     *
     * Now note that for any given ⟦x⟧, either ⟦x⟧ or ⟦1/x⟧ falls
     * into ⟦⟨-1, 1⟩⟧: hence, you can use the reciprocal formula
     * (‹atan(1/x)› is ‹2*atan(1) - atan(x)›) to find an expression
     * for the argument which always falls into the interval of
     * (fast) convergence.
     *
     * Don't forget that adding two numbers each with error ⟦≤ ε⟧
     * only guarantees that the sum has an error ⟦≤ 2ε⟧. Likewise,
     * multiplication by an exact constant also multiplies the
     * error. */

    real arg( real prec = epsilon ) const;

    /* Compute the exponential and ‹log1p› to a given precision.
     * Assume that ⟦z⟧ (‹this›) is in the area of convergence for
     * the required power series (the open unit disc for ‹log1p›,
     * the entire complex plane for ‹exp›).
     *
     * Tip: to judge the precision, use the norm (square of the
     * modulus), «not» the modulus itself. For ‹exp›, depending on
     * the argument, the terms of the power series may grow before
     * they start to shrink. Once they start to shrink and their
     * norm falls below ‹prec› squared, you have achieved the
     * required precision. How things work out with ‹log1p› is left
     * as an exercise (it's much simpler). */

    complex exp( real prec = epsilon ) const;
    complex log1p( real prec = epsilon ) const;
};
