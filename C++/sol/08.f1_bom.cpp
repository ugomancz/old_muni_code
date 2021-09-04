#include <memory>
#include <string>
#include <vector>

/* The base class. It remembers the part number and provides the
 * required interface: ‹description› and ‹part_no›. Do not forget
 * the ‹virtual› destructor! */

class part
{
    std::string _part_no;
public:
    part( std::string pn ) : _part_no( pn ) {}
    virtual std::string description() const = 0;
    std::string part_no() const { return _part_no; }
    virtual ~part() = default;
};

/* The two derived classes, 80 % boilerplate. */

class resistor : public part
{
    int _resistance;
public:
    resistor( std::string pn, int r )
        : part( pn ), _resistance( r )
    {}

    std::string description() const override
    {
        return std::string( "resistor " ) +
               std::to_string( _resistance ) + "Ω";
    }
};

class capacitor : public part
{
    int _capacitance;
public:
    capacitor( std::string pn, int c )
        : part( pn ), _capacitance( c )
    {}

    std::string description() const override
    {
        return std::string( "capacitor " ) +
               std::to_string( _capacitance ) + "μF";
    }
};

/* The smart pointer to hold and own instances of ‹part›. */

using part_ptr = std::unique_ptr< part >;

/* The ‹bom› class itself holds the parts using the above pointer.
 * It would be possible to use ‹std::map› too (and also more
 * efficient for longer part lists). Here, we use an ‹std::vector›
 * of pairs, where the pair holds the part pointer and the quantity.
 * When the item with the given order number is not on the list, we
 * throw an exception. */

class bom
{
    using item = std::pair< part_ptr, int >;
    std::vector< item > _parts;

    /* Find the item in the list: the common parts of ‹find› and
     * ‹qty›. */

    const item &_find( std::string pn ) const
    {
        for ( const auto &part : _parts )
            if ( part.first->part_no() == pn )
                return part;
        throw std::runtime_error( "part not found" );
    }

public:

    /* We don't bother with duplicates. Notice the ‹std::move›
     * though -- we have to transfer the ownership of the ‹part›
     * instance to the vector (via the pair). */

    void add( part_ptr p, int c )
    {
        _parts.emplace_back( std::move( p ), c );
    }

    const part &find( std::string pn ) const
    {
        return *_find( pn ).first;
    }

    int qty( std::string pn ) const { return _find( pn ).second; }
};

#include "f1_bom.cpp"
