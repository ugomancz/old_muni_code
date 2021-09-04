#include <memory>
#include <string>

/* In this task, you will implement a parser for a simple language
 * given as an EBNF grammar. The language in question is simplified
 * XML with attribute-less, paired tags, entities and text. In
 * addition to respecting the grammar itself, the parser must
 * enforce proper pairing of tags, i.e. each opening tag is closed
 * by an end-tag of the corresponding type. Example document:
 *
 *     <subject>
 *       <code>PB161</code>
 *       <name>Programming in C++</name>
 *       <comment>C++ &lt;3</comment>
 *     </subject>
 *
 * The grammar:
 *
 *     (* main non-terminals *)
 *     doc     = spaces, open, { doc }, close, spaces | text ;
 *     text    = { txtchar | entity } ;
 *     entity  = '&', ident, ';' | '&#', number, ';' ;
 *     open    = '<', ident, '>' ;
 *     close   = '</', ident, '>' ;
 *     spaces  = { ? any c such that std::isspace( c ) ? } ;
 *     
 *     (* simple compounds *)
 *     ident   = idchar, { idchar } ;
 *     number  = decimal, { decimal } | 'x', hex, { hex } ;
 *     
 *     (* elementary building blocks *)
 *     txtchar = ? any character except '<', '>' and '&' ? ;
 *     idchar  = 'a' | … | 'z' | 'A' | … | 'Z' ;
 *     decimal = '0' | '1' | '2' | '3' | '4' |
 *               '5' | '6' | '7' | '8' | '9' ;
 *     hex     = decimal | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' ;
 *
 * Finally, the required interface is as follows:
 */

class xml_node;
using xml_ptr = std::unique_ptr< xml_node >;
using xml_ref = const xml_node &;

/* The class ‹xml_node› represents a single node of a hierarchical
 * representation of the document. It can be either a text node
 * (with only text in it) or a compound node, with text nodes and
 * other compound nodes as children. All methods should give
 * sensible results on both node types. It is undefined behaviour if
 * ‹child_at( x )› is called for ‹x ≥ child_count()›.*/

class xml_node
{
public:
    virtual bool is_text() const;

    /* The name of the tag enclosing this node. */
    virtual std::string tag() const;

    /* The decoded text for a text node, empty otherwise. */
    virtual std::string text() const;

    virtual int child_count() const;
    virtual xml_ref child_at( int ) const;
    virtual ~xml_node() = default;
};

class xml_error
{
public:
    const char *what() const;
};

/* Check that the input document is well-formed (conforms to the
 * grammar, contains only valid entities and that tags come in
 * correctly matched pairs). Return ‹true› or ‹false› depending on
 * the outcome. Do not throw any exceptions. */

bool xml_validate( const std::string & );

/* Read a simplified-XML document, converting entities into characters.
 * You must support at least:
 *
 *   • decimal and hexadecimal entities for ASCII characters,
 *   • ‹&lt;›, ‹&gt;› and ‹&amp;›.
 *
 * The resulting tree must never contain two adjacent text nodes
 * (i.e. always read a contiguous block of text into a single node).
 * Throw ‹xml_error› if the document is ill-formed. */

xml_ptr xml_parse( const std::string & );

/* Pretty-print a simplified-XML document. Tags with a single text
 * child should be printed on a single line (however, keep
 * whitespace in text nodes intact). All other tags are formatted
 * like the example at the start: opening and closing tag on their
 * own line and all children indented 2 spaces, each child starting
 * a new line. It must be possible to read back everything that
 * comes out of ‹xml_print› using ‹xml_parse›, without errors. Use
 * entities to encode the special characters ‹<›, ‹>› and ‹&› in
 * text nodes. */

std::string xml_print( xml_ref );
