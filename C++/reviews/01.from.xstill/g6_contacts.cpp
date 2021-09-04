/* We will look at using collections of objects. We only know one type of
 * collection: a dynamic array, so that's what we will use. The objects we will
 * consider are simple entries in a contact list: they have a name and a phone
 * number (both stored as strings). */

#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <utility>

/* We need ‹contact› to possess a two-parameter constructor (which
 * initializes both its fields) and two getters (methods), ‹name›
 * and ‹phone›. */

class contact {
private:
    const std::string contact_name, contact_phone;
public:
    /** chválím správně použitý move **/
    contact(std::string contact_name, std::string contact_phone) : contact_name(std::move(contact_name)),
                                                                   contact_phone(std::move(contact_phone)) {}

    std::string name() const {
        return contact_name;
    }

    std::string phone() const {
        return contact_phone;
    }
};

using contacts = std::vector<contact>; /* type alias */

/* Let's write a helper function which checks whether the string
 * ‹small› is a prefix of the string ‹big›. */

bool is_prefix(const std::string &small, const std::string &big) {
    /** tohle se hrozně rozbije pokud ‹small.size()› > ‹big.size()› **/
    for (unsigned int i = 0; i < small.length(); i++) {
        if (small[i] != big[i]) {
            return false;
        }
    }
    return true;
}

/* And finally, a function to return all contacts whose names start
 * with the given prefix (use ‹is_prefix› in a loop). */

contacts search(const contacts &list, const std::string &prefix) {
    contacts result;
    std::copy_if(list.begin(), list.end(), std::back_inserter(result),
                 [prefix](const contact &c) { return is_prefix(prefix, c.name()); });
    return result;
}

int main()
{
    contacts list;
    list.emplace_back( "anna",  "123123" );
    list.emplace_back( "aisha", "111321" );
    list.emplace_back( "bob",   "872354" );
    list.emplace_back( "fred",  "131321" );
    list.emplace_back( "frank", "745654" );

    /* do some filtering */
    contacts all = search( list, "" );
    contacts a_team = search( list, "a" );
    contacts fr = search( list, "fr" );
    contacts bob = search( list, "bob" );

    /* check sizes */
    assert( all.size() == 5 );
    assert( a_team.size() == 2 );
    assert( fr.size() == 2 );
    assert( bob.size() == 1 );

    /* check presence of the right names */
    for ( const contact &c : a_team )
    {
        assert( c.name() == "anna" || c.name() == "aisha" );
        assert( c.phone() == "123123" || c.phone() == "111321" );
    }

    for ( const contact &c : fr )
        assert( c.name() == "frank" || c.name() == "fred" );

    assert( bob.front().name() == "bob" );

    /* check that we didn't get clones */
    assert( a_team.front().name() != a_team.back().name() );
    assert( fr.front().name() != fr.back().name() );
}
