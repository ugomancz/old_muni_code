#include <sstream>

class card
{
    char suit, rank;
public:

    friend std::ostream &operator<<( std::ostream &o, card c )
    {
        return o << c.rank << c.suit;
    }

    friend std::istream &operator>>( std::istream &i, card &c )
    {
        char ch;
        i >> ch;

        if ( ( !std::isdigit( ch ) &&
                ch != 'A' && ch != 'J' && ch != 'Q' &&
                ch != 'K' && ch != 'T' ) ||
             ( i.peek() != 'D' && i.peek() != 'S' &&
               i.peek() != 'H' && i.peek() != 'C' ) ||
             ch == '0' )
        {
            i.unget();
            i.setstate( i.failbit );
            return i;
        }

        c.rank = ch;
        return i >> c.suit;
    }
};

#include "f3_cards.cpp"
