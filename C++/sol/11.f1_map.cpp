/* We first define the iterator. It is convenient to take the
 * «underlying iterator» as a type parameter (instead of the
 * container), though the latter would also work. The other type
 * parameter is the lambda to call on each dereference. */

template< typename iterator_t, typename fun_t >
struct map_iterator
{
    iterator_t it;
    const fun_t &fun;

    /* Construct an iterator. The signature makes template argument
     * deduction work, which we will use to our advantage below. */

    map_iterator( iterator_t it, const fun_t &fun )
        : it( it ), fun( fun )
    {}

    /* The dereference operator first dereferences the underlying
     * iterator, applies ‹fun› to it and returns the result. The
     * return type of the dereference operator is tricky, so we let
     * the compiler figure it out for us. */

    auto operator*() const { return fun( *it ); }

    /* Pre-increment simply calls the underlying pre-increment. */

    map_iterator &operator++() { ++it; return *this; }

    /* Same thing with inequality. */

    bool operator!=( const map_iterator &o ) const
    {
        return it != o.it;
    }
};

/* The ‹map› class template. Here we take the underlying «container»
 * and the type of the lambda as parameters, since those are what
 * the user will supply as arguments to the constructor. This way,
 * template argument deduction will work for users as expected. */

template< typename container_t, typename fun_t >
struct map
{
    /* There are two ways to go about building the iterator type.
     * One is explicitly, by figuring out the type of the underlying
     * iterator (i.e. the iterator of ‹container_t› and creating an
     * explicit instance of ‹map_iterator›. We will use this in
     * ‹begin›. */

    using underlying = typename container_t::const_iterator;
    using iterator = map_iterator< underlying, fun_t >;

    const container_t &container;
    const fun_t &fun;

    /* The ‹begin› method needs to construct a suitable
     * ‹map_iterator›: we built the correct type above, so we can
     * use that as the return type of ‹begin›, then use ‹return›
     * with braces to call the constructor. */

    iterator begin() const { return { container.begin(), fun }; }

    /* An alternative, which does not need to mention the type of
     * the underlying iterator, but instead relies on the argument
     * deduction that we were careful to build into the constructor
     * of ‹map_iterator›. */

    auto end() const
    {
        return map_iterator( container.end(), fun );
    }

    /* Finally the constructor of ‹map› which lets us conveniently
     * create instances through template argument deduction. */

    map( const container_t &c, const fun_t &f )
        : container( c ), fun( f )
    {}
};

#include "f1_map.cpp"
